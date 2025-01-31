#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(){

    int i, j;
    char dammy;
    int N,M;
    int ans;

    scanf("%d %d", &N, &M);

    if(N == 1 || M == 1){
        ans = N * M - 2;
    }else if(N ==2 || M ==2){
        ans = 0;
    }else{
        ans = N * M - 2 * (N - 1) - 2 * (M - 1);
    }

    
    printf("%d", ans);

    return 0;
}



int max(int a, int b){
    if(a > b){
        return a;
    }else{
        return b;
    }
}