#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#include <openssl/sha.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

int socket_init(unsigned short port){
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        printf("create socket error: %d - %s\n", errno, strerror(errno));
        return 0;
    }

    // 设置端口复用
    int opt = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        printf("setsockopt SO_REUSEADDR error: %d - %s\n", errno, strerror(errno));
        return -1;
    }

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr_in)) == -1) {
        printf("bind socket error: %d - %s\n", errno, strerror(errno));
        return -1;
    }
 
    if (listen(listenfd, 128) == -1) {
        printf("listen socket error: %d - %s\n", errno, strerror(errno));
        return -1;
    }

    return listenfd;
}

#define BUFFER_LENGTH       4096
#define MAX_EPOLL_EVENTS    1024
#define SERVER_PORT         5000
#define LISTENFD_COUNT      100

#define GUID    "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"

enum {
    WS_HANDSHAKE = 0,
    WS_TRANMISSION = 1,
    WS_END
};

typedef int (*CALLBACK)(void* arg, int fd);

struct item {
    int fd;
    int events;
	CALLBACK event_cb;
    int status;             // 是否在epoll树上
    long last_active;       // 上次激活时间
    unsigned char buffer[BUFFER_LENGTH];
    int length;
    int status_machine;
};

struct itemblock {
    struct itemblock* itemblock_next;
    struct item* items;
};

struct reactor {
    int epfd;
    int itemblock_count;
    struct itemblock* itemblock_first;
};

int base64_encode(char *in_str, int in_len, char *out_str) {    
	BIO *b64, *bio;    
	BUF_MEM *bptr = NULL;    
	size_t size = 0;    

	if (in_str == NULL || out_str == NULL)        
		return -1;    

	b64 = BIO_new(BIO_f_base64());    
	bio = BIO_new(BIO_s_mem());    
	bio = BIO_push(b64, bio);
	
	BIO_write(bio, in_str, in_len);    
	BIO_flush(bio);    

	BIO_get_mem_ptr(bio, &bptr);    
	memcpy(out_str, bptr->data, bptr->length);    
	out_str[bptr->length-1] = '\0';    
	size = bptr->length;    

	BIO_free_all(bio);    
	return size;
}

int readline(char* allbuf, int pos, char* linebuf)
{
    int len = strlen(allbuf);

    for (; pos < len; ++pos) {
        if ((allbuf[pos] == '\r') && (allbuf[pos+1] == '\n')) {
            return pos + 2;
        } else {
            *(linebuf++) = allbuf[pos];
        }
    }

    return -1;
}

int reactor_init(struct reactor* r)
{
    if (r == NULL)   return -1;
    memset(r, 0, sizeof(struct reactor));

    r->epfd = epoll_create(1);
    if (r->epfd < 0) {
        printf("epoll_create epfd error: %d - %s\n", errno, strerror(errno));
        return -1;
    }

    r->itemblock_first = (struct itemblock*)malloc(sizeof(struct itemblock));
    if (r->itemblock_first == NULL) {
        printf("malloc sizeof(struct itemblock) failure\n");
        close(r->epfd);
        return -2;
    }
    memset(r->itemblock_first, 0, sizeof(struct itemblock));

    r->itemblock_first->itemblock_next = NULL;
    r->itemblock_first->items = (struct item*)malloc(MAX_EPOLL_EVENTS*sizeof(struct item));
    if (r->itemblock_first->items == NULL) {
        printf("malloc MAX_EPOLL_EVENTS*sizeof(struct item) failure\n");
        close(r->epfd);
        free(r->itemblock_first);
        return -2;
    }
    memset(r->itemblock_first->items, 0, MAX_EPOLL_EVENTS*sizeof(struct item));

    ++(r->itemblock_count);

    return 0;
}

int reactor_malloc(struct reactor* r)
{
    struct itemblock* ib = r->itemblock_first;
    while (ib->itemblock_next != NULL)  ib = ib->itemblock_next;

    ib->itemblock_next = (struct itemblock*)malloc(sizeof(struct itemblock));
    if (ib->itemblock_next == NULL) {
        printf("malloc sizeof(struct itemblock) failure\n");
        return -2;
    }
    memset(ib->itemblock_next, 0, sizeof(struct itemblock));

    ib->itemblock_next->itemblock_next = NULL;
    ib->itemblock_next->items = (struct item*)malloc(MAX_EPOLL_EVENTS*sizeof(struct item));
    if (ib->itemblock_next->items == NULL) {
        printf("malloc MAX_EPOLL_EVENTS*sizeof(struct item) failure\n");
        return -2;
    }
    memset(ib->itemblock_next->items, 0, MAX_EPOLL_EVENTS*sizeof(struct item));

    ++(r->itemblock_count);

    return 0;
}


struct item* reactor_index(struct reactor* r, int socketfd)
{
    int itemblock_index = socketfd / MAX_EPOLL_EVENTS;

    while (itemblock_index >= r->itemblock_count)   reactor_malloc(r);

    int i = 0;
    struct itemblock* ib = r->itemblock_first;
    while ((i++ < itemblock_index) && (ib != NULL))     ib = ib->itemblock_next;

    return &(ib->items[socketfd % MAX_EPOLL_EVENTS]);
}

void reactor_item_set(struct item* it, int fd, CALLBACK callback)
{
    it->fd = fd;
    it->event_cb = callback;
    it->events = 0;
    it->last_active = time(NULL);
}

int reactor_event_add(int epfd, int event, struct item* it)
{
    struct epoll_event ev;
    memset(&ev, 0, sizeof(struct epoll_event));

    ev.data.ptr = it;
    ev.events = it->events = event;

    int op;
    if (it->status == 1) {
        op = EPOLL_CTL_MOD;
    } else {
        op = EPOLL_CTL_ADD;
        it->status = 1;
    }

    if (epoll_ctl(epfd, op, it->fd, &ev) < 0) {
        printf("epoll_ctl EPOLL_CTL_ADD/EPOLL_CTL_MOD error: %d - %s\n", errno, strerror(errno));
        return -1;
    }

    return 0;
}


int reactor_addlistener(struct reactor* r, int listenfd, CALLBACK accept_cb)
{
    if(r == NULL)   return -1;
    if(r->itemblock_first == NULL)    return -1;
    
    struct item* it = reactor_index(r, listenfd);
    reactor_item_set(it, listenfd, accept_cb);
    reactor_event_add(r->epfd, EPOLLIN, it);

    return 0;
}

int reactor_del(int epfd, struct item* it)
{
    if (it->status != 1)     return -1;

    if (epoll_ctl(epfd, EPOLL_CTL_DEL, it->fd, NULL) < 0) {
        printf("epoll_ctl EPOLL_CTL_DEL error: %d - %s\n", errno, strerror(errno));
        return -1;
    }

    close(it->fd);

    memset(it, 0, sizeof(struct item));
    it->fd = -1;
    it->event_cb = NULL;

    return 0;
}

void umask(char* payload, int length, char* mask_key)
{

}

int handshake(struct item* it)
{

}

int transmission(struct item* it)
{

}

int websocket_request(struct item* it)
{
    if (it->status_machine == WS_HANDSHAKE) {

        it->status_machine = WS_TRANMISSION;
    } else if (it->status_machine == WS_TRANMISSION) {

    }
}



int send_callback(void* arg, int fd);

int recv_callback(void* arg, int fd)
{
    struct reactor* r = (struct reactor*)arg;
    struct item* it = reactor_index(r, fd);
    if (it == NULL)     return -1;

    memset(it->buffer, 0, sizeof(it->buffer));
    int n = recv(fd, it->buffer, BUFFER_LENGTH, 0);
    if (n > 0) {
        it->length = n;
        printf("fd: %d, machine: %d, recv_cb: %s\n", fd, it->status_machine, it->buffer);



        reactor_item_set(it, fd, send_callback);
        reactor_event_add(r->epfd, EPOLLOUT, it);
    } else if (n = 0) {
        reactor_del(r->epfd, it);
        printf("fd: %d, recv_cb --> disconnect\n", fd);
    } else {
        reactor_del(r->epfd, it);
        printf("fd: %d, recv_cb error: %d - %s", fd, errno, strerror(errno));
    }

    return n;
}

int send_callback(void* arg, int fd)
{
    struct reactor* r = (struct reactor*)arg;
    struct item* it = reactor_index(r, fd);
    if (it == NULL)     return -1;

    int n = send(fd, it->buffer, it->length, 0);
    if (n > 0) {
        printf("fd: %d, send_cb: %s\n", fd, it->buffer);

        reactor_item_set(it, fd, recv_callback);
        reactor_event_add(r->epfd, EPOLLIN, it);
    } else {
        reactor_del(r->epfd, it);
        printf("fd: %d, send_cb error: %d - %s", fd, errno, strerror(errno));
    }

    return n;
}

int accept_callback(void* arg, int fd)
{
    struct reactor* r = (struct reactor*)arg;

    struct sockaddr_in clientAddr;
    socklen_t len = sizeof(struct sockaddr_in);
    int connfd = accept(fd, (struct sockaddr*)&clientAddr, &len);
    if(connfd == -1){
        printf("accept socket error: %d - %s\n", errno, strerror(errno));
	    return -1;
    }

    struct item* it = reactor_index(r, connfd);
    if(it == NULL)  return -1;

    it->status_machine = WS_HANDSHAKE;

    reactor_item_set(it, connfd, recv_callback);
    reactor_event_add(r->epfd, EPOLLIN, it);

    printf("new connect [%s:%d], position: %d, it->fd = %d\n", 
            inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), connfd, it->fd);

    return 0;
}

int reactor_run(struct reactor* r)
{
    if (r == NULL)   return -1;
    if (r->itemblock_first == NULL)  return -1;
    if (r->itemblock_count == 0)    return -1;

    struct epoll_event evs[MAX_EPOLL_EVENTS+1];
    memset(evs, 0, sizeof(struct epoll_event));

    while (1) {
        int nready = epoll_wait(r->epfd, evs, MAX_EPOLL_EVENTS, -1);
        if (nready < 0) {
            printf("epoll_wait error: %d - %s\n", errno, strerror(errno));
            continue;
        }

        struct item* it = NULL; 
        for (int i = 0; i < nready; ++i) {
            it = (struct item*)evs[i].data.ptr;
            if ((evs[i].events & EPOLLIN) && (it->events & EPOLLIN)) {
                    it->event_cb(r, it->fd);
            }

            if ((evs[i].events & EPOLLOUT) && (it->events & EPOLLOUT)) {
                it->event_cb(r, it->fd);
            }
        }
    }
}

void reactor_destroy(struct reactor* r)
{
    close(r->epfd);

    struct itemblock* ib = r->itemblock_first;
    struct itemblock* ib_next = NULL;

    while (ib != NULL) {
        ib_next = ib->itemblock_next;

        free(ib->items);    ib->items = NULL;
        free(ib);   ib = NULL;

        ib = ib_next;
    }
}


int main(int argc, char* argv[])
{
    unsigned short port = SERVER_PORT;
    if (argc == 2)      port = (unsigned short)atoi(argv[1]);

    struct reactor* R = (struct reactor*)malloc(sizeof(struct reactor));
    reactor_init(R);

    int listenfds[LISTENFD_COUNT] = {0};
    for (int i = 0; i < LISTENFD_COUNT; ++i) {
        listenfds[i] = socket_init(port+i);
        reactor_addlistener(R, listenfds[i], accept_callback);
    }

    reactor_run(R);

    reactor_destroy(R);

    for (int i = 0; i < LISTENFD_COUNT; ++i)    close(listenfds[i]);

    free(R);    R = NULL;

    return 0;
}

