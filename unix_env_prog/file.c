#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    int fd = open(argv[1], O_RDWR | O_CREAT, 0755);
    if (fd < 0) {
        perror("open error");
        return EXIT_FAILURE;
    }

    write(fd, "hello world", strlen("hello world"));

    lseek(fd, 0, SEEK_SET);
    
    char buf[1024] = {0};
    int n = read(fd, buf, sizeof(buf));
    printf("buf_len = [%d], buf = [%s]\n", n, buf);

    close(fd);

    return EXIT_SUCCESS;
}