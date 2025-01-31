#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int sheeps, wolves;
    sheeps = atoi(argv[1]);
    wolves = atoi(argv[2]);

    if (sheeps < wolves) {
        printf("unsafe");
    } else {
        printf("safe");
    }

    return 0;
}