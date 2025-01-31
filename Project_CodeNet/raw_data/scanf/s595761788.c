#include <stdio.h>

int main(void) {
	int N, D, X;
	int A[128];
	int i;
	int tomatuharuka = 0;
	if (scanf("%d", &N) != 1) return 1;
	if (scanf("%d%d", &D, &X) != 2) return 1;
	for (i = 0; i < N; i++) {
		if (scanf("%d", &A[i]) != 1) return 1;
	}

	for (i = 0; i < N; i++) {
		tomatuharuka += (D + A[i] - 1) / A[i];
	}
	printf("%d\n", X + tomatuharuka);

	return 0;
}
