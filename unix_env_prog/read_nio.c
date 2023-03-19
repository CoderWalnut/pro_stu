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

    char buf[1024] = {0};
    int n = read(fd, buf, sizeof(buf));
    printf("first buf_len = [%d], buf = [%s]\n", n, buf);

    memset(buf, 0, sizeof(buf));
    n = read(fd, buf, sizeof(buf));
    printf("second buf_len = [%d], buf = [%s]\n", n, buf);

    close(fd);
}