#include<stdio.h>

int main() {
	int X, Y;
	scanf("%d%d", &X, &Y);

	if (X % Y == 0)
	{
		printf("-1");
	}
	else 
	{
		printf("%d", X);
	}
	return 0;
}