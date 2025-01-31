#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
        int a = strtol(argv[1], ((void *)0), 10);
        int b = strtol(argv[2], ((void *)0), 10);
        float t = strtod(argv[3], ((void *)0));
        int num = 0;
        int i, j=(t+0.5)/a;
        for(i=0; i<j; i++) {
                num += b;
        }
        printf("%d\n", num);
        return 0;
}
