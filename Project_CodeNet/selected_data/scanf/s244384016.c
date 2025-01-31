#include <stdio.h>

int main(void){
    int K,N;
    int A[400001]={};
    scanf("%d%d",&K,&N);
    int x;
    for (int i=0; i<N; i++) {
        scanf("%d",&x);
        A[x]=1;
        A[x+K]=1;
    }
    int max=0;
    int f=0;
    int tmp;
    for (int i=0; i<(2*K); i++) {
        if (A[i]) {
            if (f) {
                if (max<(i-tmp)) {
                    max=(i-tmp);
                }
                tmp=i;
            }
            else{
                f=1;
                tmp=i;
            }
        }
    }
    printf("%d\n",K-max);
    return 0;
}
