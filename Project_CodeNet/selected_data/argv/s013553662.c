#include <stdio.h>
#include <stdlib.h>

int main(int argc,char * argv[]){
    int n;
    n=atoi(argv[1]);
    if(n<3||10000<n){
        return 0;
    }
    int i=1;
    int x;
    for(i=1;i<=n;i++){
        x=i;
        if(x%3==0){
            printf("%d ",i);
        }
        else if(x%10==3){
            printf("%d ",i);
        }
    }
    printf("\n");
}
