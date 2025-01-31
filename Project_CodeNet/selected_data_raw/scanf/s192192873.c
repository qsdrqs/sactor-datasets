#include<stdio.h>
int isTrue(int *A, int n, int target) {
    int i;
    for (i=n-1; i>=0; i--) {
        if(A[i] == target) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    int n,m;
    int i,j;
    int c=0;
    int a,b;
    int answer=0;
    scanf("%d%d",&n,&m);
    int A[m];
    for (i=0; i<m; i++) {
        scanf("%d%d",&a,&b);
        if (a == 1) {
            if (answer==0) {
                answer = isTrue(A,c,b);
            }
            A[c] = b;
            c++;
        } else if (b == n) {
            if (answer==0) {
                answer = isTrue(A,c,a);
            }
            A[c] = a;
            c++;
        }
    }
    if (answer == 1) {
        printf("POSSIBLE\n");
    } else {
        printf("IMPOSSIBLE\n");
    }
    return 0;
}
