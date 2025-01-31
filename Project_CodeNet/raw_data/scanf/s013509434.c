#include <stdio.h>
int main(void){
	int n,m,i,j;
	int dp[100001],t[100001]={0};
	dp[0] = 1;
	scanf("%d %d",&n,&m);
	for(i=0;i<m;i++){
		scanf("%d",&j);
		t[j] = 1;
	}
	for(i=1;i<=n;i++){
		if(t[i] == 0){
			if(i>=2) dp[i] = dp[i-1] + dp[i-2];
			else if(i == 1) dp[i] = dp[i-1];
		}
		else dp[i] = 0;
		dp[i] %= 1000000007;
	}
	printf("%d\n",dp[n]);
	return 0;
}