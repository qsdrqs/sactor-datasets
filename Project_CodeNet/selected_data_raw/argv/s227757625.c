#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int c = a * b;
    if (c % 2 == 1){
        puts("Odd");
    } else {
        puts("Even");
    }
    return 0;
}