#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int s,w;
    s=atoi(argv[1]);
    w=atoi(argv[2]);
    if(w>=s){
        printf("unsafe");
    }else{
        printf("safe");
    }
    return 0;
}
