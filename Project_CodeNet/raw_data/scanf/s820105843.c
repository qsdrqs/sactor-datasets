#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1
#define NINF -1
#define PINF 1E9+1

int n;
double *p;
double *dp; // x:throw coins y:surface

int pos(int x,int y)
{
	return n*y+x;
}

int main(void)
{
	int i,j;
	double ans;
	scanf("%d",&n);
	p = (double *)malloc(sizeof(double) * n);
	for (i=0;i<n;i++) scanf("%lf",&p[i]);

	dp = (double *)malloc(sizeof(double) * n*(n+1));
	if (dp==NULL) {
		perror("malloc");
		exit(1);
	}
	for (j=0;j<n+1;j++) {
		for (i=0;i<n;i++) {
			dp[pos(i,j)] = 0;
		}
	}
	dp[pos(0,1)] = p[0];
	dp[pos(0,0)] = 1.0 - p[0];

	for (j=0;j<n+1;j++) {
		for (i=1;i<n;i++) {
			dp[pos(i,j)] += dp[pos(i-1,j)] * (1.0-p[i]);
			if (j==0) continue;
			dp[pos(i,j)] += dp[pos(i-1,j-1)] * p[i];
		}
	}

	ans = 0.0;
	for (j=(n+1)/2;j<n+1;j++) {
		ans += dp[pos(n-1,j)];
	}
	printf("%f\n",ans);

	free(p);
	free(dp);
	return 0;
}
