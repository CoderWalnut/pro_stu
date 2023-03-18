#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SERVER_PORT 6666
#define MAX_SIZE 1024
#define INET_STRLEN 64

int main(int argc, char* argv[]) {
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(struct sockaddr_in));
    serveraddr.sin_family =  AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(SERVER_PORT);
    bind(listenfd, (const struct sockaddr *)&serveraddr, sizeof(struct sockaddr_in));
    listen(listenfd, 512);

    struct sockaddr_in clientaddr;
    socklen_t clientAddrLen;
    int connfd = -1;
    ssize_t n = 0;
    unsigned char buf[MAX_SIZE] = {0};
    char inetstr[INET_STRLEN]= {0};
    printf("Accepting connections ...\n");
    while (1) {
        memset(&clientaddr, 0, sizeof(struct sockaddr_in));
        clientAddrLen = sizeof(struct sockaddr_in);    //每次都要重新赋值
        connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientAddrLen);

        n =  read(connfd, buf, MAX_SIZE);
        printf("received from %s at PORT %d\n",
                inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, inetstr, INET_STRLEN), ntohs(clientaddr.sin_port));
        
        for (int i = 0; i < n; i++) {
            buf[i] = toupper(buf[i]);
        }

        write(connfd, buf, n);

        close(connfd);
    }


    return EXIT_FAILURE;
}
