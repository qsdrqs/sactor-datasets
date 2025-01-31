#include <stdio.h>

int p[92][92];
int step(int x,int y){
    p[x][y]=0;
    int res=1;
    if (p[x+1][y]==1) {
        res=((res) > (step(x+1, y)+1) ? (res) : (step(x+1, y)+1));
    }
    if (p[x-1][y]==1) {
        res=((res) > (step(x-1, y)+1) ? (res) : (step(x-1, y)+1));
    }
    if (p[x][y+1]==1) {
        res=((res) > (step(x, y+1)+1) ? (res) : (step(x, y+1)+1));
    }
    if (p[x][y-1]==1) {
        res=((res) > (step(x, y-1)+1) ? (res) : (step(x, y-1)+1));
    }
    p[x][y]=1;
    return res;
};
int main(){
    while (1) {
        int m,n;
        scanf("%d%d",&m,&n);
        if (m==0&&n==0) {
            return 0;
        }
        int i,j,ans=0;
        for (i=0; i<n+2; i++) {
            for (j=0; j<m+2; j++) {
                if (i==0||j==0||i==n+1||j==m+1) {
                    p[j][i]=0;
                }else{
                    scanf("%d",&p[j][i]);
                }
            }
        }
        for (i=1; i<=n; i++) {
            for (j=1; j<=m; j++) {
                if (p[j][i]==1) {
                    ans=((ans) > (step(j,i)) ? (ans) : (step(j,i)));
                }
            }
        }
        printf("%d\n",ans);
    }
}
