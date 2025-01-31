#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

        int x, a, b;

        x = atoi(argv[1]);
        a = atoi(argv[2]);
        b = atoi(argv[3]);

        if((x >= 1 && x <= 1000) && (a >= 1 && a <= 1000) && (b >= 1 && b <= 1000)){
                if(abs(a-x) > abs(b-x)){
                        printf("B\n");
                }else if(abs(a-x) < abs(b-x)){
                        printf("A\n");
                }else if(a == b){
                        return 1;
                }
        }





return 0;
}