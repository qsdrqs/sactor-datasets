#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int result = 1; 
    int power = 3;
    int x = atoi(argv[1]);


    int i;
    for(i = 0; i < power; i++){
        result = result * x;
    }

    printf("%d\n",result);

    return 0;
}