#include <stdio.h>

int main(){
    
    int i, j, n, u, k, v, N[101][101];
    
    scanf("%d", &n);
    
    for(i = 1; i <= n; i++){
       scanf("%d", &u);
       scanf("%d", &k);
       for(j = 1; j <= k; j++){
            scanf("%d", &v);
            N[u][v] = 1;
        }
    }
    
    for(i = 1; i <= n; i++){
        for(j = 1; j <= n; j++){
            if(N[i][j] != 1) N[i][j] = 0;
            if(i == 0) printf(" ");
            printf("%d", N[i][j]);
        }
        printf("\n");
    }
    return 0;
}