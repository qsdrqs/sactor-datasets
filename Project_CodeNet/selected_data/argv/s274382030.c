#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int result = 1;
    int power = 3; //cubic
    int x = atoi(argv[1]);
    //loop
    int i;
    for(i = 0; i < power; i++){
        result = result * x;
    }
    printf("%d\n",result);
    return 0;
}
