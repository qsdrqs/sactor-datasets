#include<stdio.h>
int main()

{
	int N;
	scanf("%d", &N);
	int A[N];
	int max=0;
	int r;
	
	for(r=0; r<N; r++)	scanf("%d", &A[r]);
	
	for(r=0; r<N; r++)
	{
		if (A[r] > max) max = A[r];
	}
	
	int min = max;
	
	for(r=0; r<N; r++)
	{
		if (A[r] < min) min = A[r];
	}
	
	printf("%d", max-min);
	
	return 0;
	
}