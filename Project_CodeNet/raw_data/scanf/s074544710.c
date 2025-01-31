#include <stdio.h>

int main()
{
	int A, B, C;
	scanf("%d %d %d[1-9]",&A, &B, &C);
	if (A==B && A==C && B==C){
		printf("No\n");
	}
	else if (A==B, B==C, C==A){
		printf("Yes\n");
	}
	return 0;
}