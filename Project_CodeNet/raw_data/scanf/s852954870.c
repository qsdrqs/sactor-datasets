#include <stdio.h>

int main(){
    int N,A,B;
    int num;
    scanf("%d %d %d",&N,&A,&B);
    num = (N/(A+B))*A;
    if(N%(A+B) < A){
        num+=N%(A+B);
    }else{
        num+=A;
    }
    printf("%d",num);
    return 0;
}