#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int a=atoi(argv[1]),b=atoi(argv[2]);
    //printf("A = %d, B = %d\n",a,b);
    int result = a + b;
    if(result <= a - b){
        result = a - b;
    }
    if(result <= a * b){
        result = a * b;
    }
    printf("%d", result);
}
