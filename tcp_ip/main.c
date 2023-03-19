#include "xnet_tiny.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    xnet_init();

    printf("xnet running\n");
    while (1) {
        xnet_poll();
    }

    return 0;
}