#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int x = atoi(argv[1]);
    int a = atoi(argv[2]);
    int b = atoi(argv[3]);

    int c = b - a;
    if(c < 0) { printf("delicious\n"); }
    else if(c <= x) { printf("safe\n"); }
    else { printf("dangerous\n"); }

    return 0;
}