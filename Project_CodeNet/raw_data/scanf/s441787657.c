#include<stdio.h>
int main() {
	int n;
	scanf("%d", &n);
	if (n == 3 || n == 5 || n == 7) {
		printf("YES");
	}
	else {
		printf("NO");
	}
	return 0;
}