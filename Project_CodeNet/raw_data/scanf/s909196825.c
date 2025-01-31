/* Coached by Dukkha */
#include <stdio.h>

#define N 100000

int main() {
	static int hh[N];
	int n, i;

	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", &hh[i]);
	for (i = n - 2; i >= 0; i--)
		if (hh[i] > hh[i + 1])
			hh[i]--;
	for (i = 0; i < n - 1; i++)
		if (hh[i] > hh[i + 1]) {
			printf("No\n");
			return 0;
		}
	printf("Yes\n");
	return 0;
}
