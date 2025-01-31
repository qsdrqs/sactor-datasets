
#include <stdio.h>

long long MAX(long long a,long long b){
    if(a>b){
        return a;
    }else{
        return b;
    }
}
int main()
{
    long long n,W;
    scanf("%lld%lld",&n,&W);
    long long w[n],v[n];
    for(int i=0;i<n;i++){
        scanf("%lld%lld",&w[i],&v[i]);
    }
    long long dp[n+1][W+2];
    for(int i=0;i<=n;i++){
        for(int j=0;j<=W+1;j++){
            dp[i][j]=0;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<=W;j++){
            dp[i+1][j]=dp[i][j];
            if(j>=w[i]){
            dp[i+1][j]=MAX(dp[i][j-w[i]]+v[i],dp[i][j]);
            }else{
                dp[i+1][j]=dp[i][j];
            }
        }
    }
    printf("%lld",dp[n][W]);
    return 0;
}
