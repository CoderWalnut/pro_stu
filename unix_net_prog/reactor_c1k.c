#include <stdio.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int init_server(unsigned short port){
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        printf("create socket error: %d-%s\n", errno, strerror(errno));
        return 0;
    }

    // 设置端口复用
    int opt = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        printf("setsockopt SO_REUSEADDR error: %d-%s\n", errno, strerror(errno));
        return -1;
    }

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
 
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr_in)) == -1) {
        printf("bind socket error: %d-%s\n", errno, strerror(errno));
        return -1;
    }
 
    if (listen(listenfd, 128) == -1) {
        printf("listen socket error: %d-%s\n", errno, strerror(errno));
        return -1;
    }

    return listenfd;
}

#define BUFFER_LENGTH   4096
#define MAX_EPOLL_EVENT 1024

#define NOSET_CB    0
#define READ_CB     1
#define WRITE_CB    2
#define ACCEPT_CB   3

typedef int (*CALLBACK)(int fd);

struct item {
    int fd;
    int events;
	CALLBACK event_cb;

    unsigned char rbuffer[BUFFER_LENGTH];
    unsigned int rlength;
    unsigned char sbuffer[BUFFER_LENGTH];
    unsigned int slength;
};

struct itemblock {
    struct itemblock* next;
    struct item* items;
};

struct reactor {
    int epfd;
    struct itemblock* first;
};

int reactor_init(struct reactor* r)
{
    if (r == NULL)  return -1;

    r->epfd = epoll_create(1);

    r->first = (struct itemblock*)malloc(sizeof(struct itemblock));
    if (r->first == NULL) {
        close(r->epfd);
        return -2;
    }
    memset(r->first, 0, sizeof(struct itemblock));

    r->first->next = NULL;
    r->first->items = (struct item*)malloc(MAX_EPOLL_EVENT * sizeof(struct item));
    if (r->first->items == NULL) {
        close(r->epfd);
        free(r->first);
        return -2;
    }
    memset(r->first->items, 0, (MAX_EPOLL_EVENT * sizeof(struct item)));
    for (int i = 0; i < MAX_EPOLL_EVENT; ++i) {
        r->first->items[i].fd = -1;
        r->first->items[i].events = NOSET_CB;
        r->first->items[i].event_cb = NULL;
    }

    return 0;
}

struct reactor* instance = NULL;
struct reactor* getInstance(void)   // singleton
{
    if (instance == NULL) {
        instance = (struct reactor*)malloc(sizeof(struct reactor));
        if (instance == NULL) return NULL;
        memset(instance, 0, sizeof(struct reactor));

        if (reactor_init(instance) < 0) {
            free(instance);
            return NULL;
        }
    }

    return instance;
}

int reactor_set_event(int fd, CALLBACK cb, int event)
{
    struct reactor* r = getInstance();
    struct epoll_event ev;
    memset(&ev, 0, sizeof(struct epoll_event));

    r->first->items[fd].fd = fd;
    r->first->items[fd].event_cb = cb;

    if ((event == ACCEPT_CB) || (event == READ_CB))		ev.events = EPOLLIN;
    else if (event == WRITE_CB)		ev.events = EPOLLOUT;
    ev.data.ptr = &(r->first->items[fd]);

    if (r->first->items[fd].events == NOSET_CB) {
        if (epoll_ctl(r->epfd, EPOLL_CTL_ADD, fd, &ev) < 0) {
            printf("epoll_ctl EPOLL_CTL_ADD error: %d-%s\n", errno, strerror(errno));
            return -1;
        }
        r->first->items[fd].events = event;
    } else if (r->first->items[fd].events != event) {
        if (epoll_ctl(r->epfd, EPOLL_CTL_MOD, fd, &ev) < 0) {
            printf("epoll_ctl EPOLL_CTL_MOD error: %d-%s\n", errno, strerror(errno));
            return -1;
        }
        r->first->items[fd].events = event;
    }

    return 0;
}

void reactor_loop()
{
    struct reactor* r = getInstance();
    struct epoll_event events[MAX_EPOLL_EVENT];
    memset(events, 0, (MAX_EPOLL_EVENT * sizeof(struct epoll_event)));

    while (1) {
        int nready = epoll_wait(r->epfd, events, MAX_EPOLL_EVENT, -1);
        if(nready == -1)    continue;

        struct item* it = NULL;
        for (int i = 0; i < nready; ++i) {
            it = (struct item*)events[i].data.ptr;
            it->event_cb(it->fd);
        }
    }
}

int reactor_del_event(int fd)
{
    struct reactor* r = getInstance();

    if (epoll_ctl(r->epfd, EPOLL_CTL_DEL, fd, NULL) < 0) {
        printf("epoll_ctl EPOLL_CTL_DEL error: %d-%s\n", errno, strerror(errno));
        return -1;
    }

    close(fd);	  // 先EPOLL_CTL_DEL再close

    memset(&(r->first->items[fd]), 0, sizeof(struct item));
    r->first->items[fd].fd = -1;
    r->first->items[fd].events = NOSET_CB;
    r->first->items[fd].event_cb = NULL;

    return 0;
}

int write_callback(int fd);

int read_callback(int fd)
{
    struct reactor* r = getInstance();

#if 0   // ET

    int index = 0, n = 0;
    while (index < BUFFER_LENGTH) {
        n = recv(fd, rbuffer+index, BUFFER_LENGTH-index, 0);
        if (n == -1)    break;
        else if (n > 0) {
            index += n;
        } else {
            break;
        }
    }

    if ((index == BUFFER_LENGTH) && (n != -1)) {
        reactor_set_event(fd, read_callback, READ_CB);
    } else if (n == 0) {
        reactor_del_event(fd);
    } else {
        reactor_set_event(fd, write_callback, WRITE_CB);
    }

#elif 1   // LT
    memset(r->first->items[fd].rbuffer, 0, sizeof(r->first->items[fd].rbuffer));
    int n = recv(fd, r->first->items[fd].rbuffer, BUFFER_LENGTH, 0);
    if (n == 0) {
        reactor_del_event(fd);
    } else if (n > 0) {
        r->first->items[fd].rlength = n;
        printf("READ_CB: %s\n", r->first->items[fd].rbuffer);

        memset(r->first->items[fd].sbuffer, 0, sizeof(r->first->items[fd].sbuffer));
        memcpy(r->first->items[fd].sbuffer, r->first->items[fd].rbuffer, n);
        r->first->items[fd].slength = n;

        reactor_set_event(fd, write_callback, WRITE_CB);
    }

#endif

    return 0;
}

int write_callback(int fd)
{
    struct reactor* r = getInstance();

    int n = send(fd, r->first->items[fd].sbuffer, r->first->items[fd].slength, 0);
    if (n < r->first->items[fd].slength) {
        reactor_set_event(fd, write_callback, WRITE_CB);
    } else {
        reactor_set_event(fd, read_callback, READ_CB);
    }

    return 0;
}

int accept_callback(int fd)
{
    struct sockaddr_in clientAddr;
    socklen_t len = sizeof(struct sockaddr_in);
    int connfd = accept(fd, (struct sockaddr*)&clientAddr, &len);
    if(connfd == -1){
        printf("accept socket error: %d-%s\n", errno, strerror(errno));
	    return -1;
    }

    reactor_set_event(connfd, read_callback, READ_CB);

    return 0;
}


int main(int argc, char* argv[])
{
    int listenfd = init_server(3389);

    reactor_set_event(listenfd, accept_callback, ACCEPT_CB);

    reactor_loop();

    close(listenfd);
    return 0;
}