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
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>

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

#define BUFFER_LENGTH       1024
#define MAX_EPOLL_EVENTS    1024
#define SERVER_PORT         5000
#define LISTENFD_COUNT      1
#define RESOURCE_LENGTH     1024

#define HTTP_METHOD_GET     0
#define HTTP_METHOD_POST    1

#define HTTP_WEBSERVER_HTML_ROOT    "html"

typedef int (*CALLBACK)(void* arg, int fd);

struct item {
    int fd;
    int events;
	CALLBACK event_cb;
    int status;             // 是否在epoll树上
    long last_active;       // 上次激活时间
    unsigned char rbuffer[BUFFER_LENGTH];
    int rlength;
    unsigned char sbuffer[BUFFER_LENGTH];
    int slength;
    int method;
    char resource[RESOURCE_LENGTH];
    int retCode;
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

void reactor_http_request(struct item* it)
{
    char linebuffer[1024] = {0};
    int pos = readline(it->rbuffer, 0, linebuffer);
    if (strstr(linebuffer, "GET") != NULL) {
        it->method = HTTP_METHOD_GET;

        int i = 0;
        while (linebuffer[sizeof("GET ") + i] != ' ')   ++i;
        linebuffer[sizeof("GET ") + i] = '\0';
        sprintf(it->resource, "./%s/%s", HTTP_WEBSERVER_HTML_ROOT, linebuffer + sizeof("GET "));
    } else if (strstr(linebuffer, "POST") != NULL) {
        it->method = HTTP_METHOD_POST;
    }
}


int reactor_http_response(struct item* it)
{
    if (it->method == HTTP_METHOD_GET) {
    #if 0
        const char* html = "<html><head><title>hello http</title></head><body><h1>King</h1></body></html>\r\n\r\n";
        it->slength = sprintf(it->sbuffer, 
            "HTTP/1.1 200 OK\r\n"
            "Date: Thu, 11 Nov 2021 12:28:52 GMT\r\n"
            "Content-Type: text/html;charset=ISO-8859-1\r\n"
            "Content-Length: 83\r\n\r\n%s", html
        );
    #else
        printf("resource: %s\n", it->resource);

        int filefd = open(it->resource, O_RDONLY);
        if (filefd == -1) {
            it->retCode = 404;
            it->slength = sprintf(it->sbuffer,
                "HTTP/1.1 404 Not Found\r\n"
				"Date: Thu, 11 Nov 2021 12:28:52 GMT\r\n"
				"Content-Type: text/html;charset=ISO-8859-1\r\n"
				"Content-Length: 85\r\n\r\n"
                "<html><head><title>404 Not Found</title></head><body><h1>404</h1></body></html>\r\n\r\n"
            );
        } else {
            struct stat stat_buf;
            memset(&stat_buf, 0, sizeof(struct stat));
            fstat(filefd, &stat_buf);
            close(filefd);

            if (S_ISDIR(stat_buf.st_mode)) {
                it->retCode = 404;
                it->slength = sprintf(it->sbuffer,
                "HTTP/1.1 404 Not Found\r\n"
				"Date: Thu, 11 Nov 2021 12:28:52 GMT\r\n"
				"Content-Type: text/html;charset=ISO-8859-1\r\n"
				"Content-Length: 85\r\n\r\n"
                "<html><head><title>404 Not Found</title></head><body><h1>404</h1></body></html>\r\n\r\n");
            } else if (S_ISREG(stat_buf.st_mode)) {
                it->retCode = 200;
                it->slength = sprintf(it->sbuffer,
                    "HTTP/1.1 200 OK\r\n"
			 	    "Date: Thu, 11 Nov 2021 12:28:52 GMT\r\n"
			 	    "Content-Type: text/html;charset=ISO-8859-1\r\n"
				    "Content-Length: %ld\r\n\r\n", stat_buf.st_size
                );
            }
        }
    #endif

        return it->slength;

    } else if (it->method == HTTP_METHOD_POST) {

    }
}





int send_callback(void* arg, int fd);

int recv_callback(void* arg, int fd)
{
    struct reactor* r = (struct reactor*)arg;
    struct item* it = reactor_index(r, fd);
    if (it == NULL)     return -1;

    memset(it->rbuffer, 0, sizeof(it->rbuffer));
    it->rlength = 0;

    int n = recv(fd, it->rbuffer, BUFFER_LENGTH, 0);
    if (n > 0) {
        it->rlength = n;
        printf("fd: %d, recv_cb: %s\n", fd, it->rbuffer);

        reactor_http_request(it);

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

    memset(it->sbuffer, 0, sizeof(it->sbuffer));
    it->slength = 0;
    reactor_http_response(it);

    int n = send(fd, it->sbuffer, it->slength, 0);
    if (n > 0) {
        printf("fd: %d, send_cb: %s\n", fd, it->sbuffer);

        if (it->retCode == 200) {
            int filefd = open(it->resource, O_RDONLY);
            struct stat stat_buf;
            memset(&stat_buf, 0, sizeof(struct stat));
            fstat(filefd, &stat_buf);

            sendfile(fd, filefd, NULL, stat_buf.st_size);
            close(filefd);
        }

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

