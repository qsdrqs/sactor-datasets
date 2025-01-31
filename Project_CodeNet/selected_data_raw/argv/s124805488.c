#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
        int a = atoi(argv[1]);
        int b = atoi(argv[2]);
        if (a < b) {
                printf("a < b\n");
        } else if (a > b) {
                printf("a > b\n");
        } else {
                printf("a == b\n");
        }
        return 0;
}