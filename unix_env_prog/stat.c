#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    struct stat m_stat;
    memset(&m_stat, 0, sizeof(struct stat));
    stat("./test.log", &m_stat);
    printf("mode = [%o], size = [%ld], gid = [%d], uid = [%d]\n" , m_stat.st_mode, m_stat.st_size, m_stat.st_gid, m_stat.st_uid);
}