#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
int cat = atoi(argv[1]);
int unknown = atoi(argv[2]);
int just = atoi(argv[3]);
    if(cat<= just <=cat + unknown){
            printf("YES\n");
    }else{
            printf("NO\n");
    }
}
