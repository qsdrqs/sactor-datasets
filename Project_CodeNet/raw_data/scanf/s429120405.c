#include<stdio.h>
int main(void)
{
	int K, X;
	scanf("%d", &K);
	scanf("%d", &X);
	if (K * 500 >= X)
		printf("Yes");
	else
		printf("No");
	return 0;
}