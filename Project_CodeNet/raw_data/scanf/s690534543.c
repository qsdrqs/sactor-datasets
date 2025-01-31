#include<stdio.h>

int main(void) {
	int n, m, i;
	int a[100];

	scanf("%d%d", &n, &m);

	for (i = 0; i < m; i++) {
		scanf("%d", &a[i]);
	}

	for (i = 0; i < m; i++) {
		n -= a[i];
		if (n < 0) {
			printf("-1\n");
			return 0;
		}
	}

	printf("%d\n", n);

	return 0;
}