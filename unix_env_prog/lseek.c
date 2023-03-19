#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    int fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        perror("open error");
        return EXIT_FAILURE;
    }

    int n = lseek(fd, 0 ,SEEK_END);
    printf("file_size = [%d]\n", n);

    n = lseek(fd, 1000, SEEK_END);
    printf("extr file_size = [%d]\n", n);

    write(fd, "a", strlen("a"));

    close(fd);

    return EXIT_SUCCESS;
}