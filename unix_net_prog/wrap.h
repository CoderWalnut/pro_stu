#ifndef __WRAP_H__
#define __WRAP_H__

#include <sys/types.h>
#include <arpa/inet.h>

void perr_exit(const char *s);

int Socket(int family, int type, int protocol);

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);

int Bind(int fd, const struct sockaddr *sa, socklen_t salen);

int Connect(int fd, const struct sockaddr *sa, socklen_t salen);

int Listen(int fd, int backlog);

ssize_t Read(int fd, void *ptr, size_t nbytes);

ssize_t Write(int fd, const void *ptr, size_t nbytes);

int Close(int fd);

ssize_t Readn(int fd, void *vptr, size_t n);

ssize_t Writen(int fd, const void *vptr, size_t n);

ssize_t my_read(int fd, char *ptr);

ssize_t Readline(int fd, void *vptr, size_t maxlen);

#endif