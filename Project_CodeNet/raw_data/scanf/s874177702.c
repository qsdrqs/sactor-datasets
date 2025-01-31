#include <stdio.h>

int main(void)
{
	long long int n, k, i, ans=0, max, min;
	int mod = 1000000007;
	
	scanf("%lld%lld", &n, &k);
	
	for (i = k; i <= n + 1; i++) {
		max = i * (2 * n - i + 1) / 2;
		min = i * (i - 1) / 2;
		ans += max - min + 1;
		ans = ans % mod;
	}

	printf("%lld", ans);
	return 0;
}