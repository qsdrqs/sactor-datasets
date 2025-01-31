#include <stdio.h>

int main(){
    int n,c,k,a;
    scanf("%d%d",&n,&c);
    int i;
    for(i=0;i<c;i++){
        scanf("%d",&a);
        k+=a;
    }
    if((k%n)!=0) k+=n;
    printf("%d",k/n);
}
