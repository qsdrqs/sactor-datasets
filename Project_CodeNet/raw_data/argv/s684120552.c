#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
        int n;

        n = atoi(argv[1]);
        printf("%d\n", n*n*n);
        return 0;
}