#include<stdio.h>

int main(){
    int N,M;
    int a[100+1] = {0};
    int all=0;
    int i,j,tmp;

    scanf("%d %d", &N, &M);

    for( i = 1; i <= N; i++ ){
        scanf("%d", &a[i]);
        all += a[i];
    }

    for( i = 1; i <= N-1; i++ ){
        for( j = i+1; j <= N; j++ ){
            if( a[i] < a[j] ){
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }

/*    for(i=1;i<=N;i++){
        printf("%d ", a[i]);
    }
    printf("\n");
*/

    if( a[M] >= (double)all/(4*M) ) printf("Yes\n");
    else printf("No\n");

    return 0;
}


