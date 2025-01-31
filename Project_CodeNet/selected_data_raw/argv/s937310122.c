#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
        int a = strtol(argv[1], NULL, 10);
        int b = strtol(argv[2], NULL, 10);
        float t = strtod(argv[3], NULL);
        int num = 0;
        int i, j=(t+0.5)/a;
        for(i=0; i<j; i++) {
                num += b;
        }
        printf("%d\n", num);
        return 0;
}
