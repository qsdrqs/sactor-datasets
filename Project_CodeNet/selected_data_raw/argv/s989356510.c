#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

        int x, a, b;

        x = atoi(argv[1]);
        a = atoi(argv[2]);
        b = atoi(argv[3]);

        if(abs(a-x) > abs(b-x)){
                printf("B\n");
        }else if(abs(a-x) < abs(b-x)){
                printf("A\n");
        }





return 0;
}