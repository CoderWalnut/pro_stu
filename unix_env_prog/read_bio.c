#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    // int fd = open("/dev/tty", O_RDWR);
    // if (fd < 0) {
    //     perror("open error");
    //     return EXIT_FAILURE;
    // }

    char buf[1024] = {0};
    int n = read(STDIN_FILENO, buf, sizeof(buf));
    printf("first buf_len = [%d], buf = [%s]\n", n, buf);

    // close(fd);

    return EXIT_SUCCESS;
}