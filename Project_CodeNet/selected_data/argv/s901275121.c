#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
    int x = 2;
    printf("%d\n", atoi(argv[1])/x + atoi(argv[1])%x);
    return 0;
}
