#include<stdio.h>


int main() {
	int i, j, k, f = 0, n, t, m, b;
	int a[1100000];
	long long int q;

	scanf("%d", &n);
	for (i = 0;i < n;i++) {
		scanf("%d", &a[i]);
	}

	for (i = 0;i < n;i++) {
		if (i < 0) {
			i = i * (-1);
			f = f + 1;
		}
	}

	m = 0;

	if (f % 2 == 1) {
		for (i = 0;i < n;i++) {
			if (a[m] > a[i]) {
				m = i;
			}
		}
	}
	
	q = 0;
	
	for (i = 0;i < n;i++) {
		q = q + a[i];
	}

	q = q - m * 2;

	printf("%lld",q);


	return 0;
}