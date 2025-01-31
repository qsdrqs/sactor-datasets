#include <stdio.h>

int main(){
    long int A, B, K;
    scanf("%ld", &K);
    scanf("%ld", &A);
    scanf("%ld", &B);

    if(A*K<=B){
        printf("OK");
    }else{
        printf("NG");
    }

    return 0;
}