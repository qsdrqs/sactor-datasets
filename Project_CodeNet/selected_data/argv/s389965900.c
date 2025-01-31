#include <stdio.h>
#include <stdlib.h> 

int main(int argc, char *argv[]){
    int x = atoi(argv[1]);
    int y = x + x*x + x*x*x;
    printf("%d\n",y);
}
