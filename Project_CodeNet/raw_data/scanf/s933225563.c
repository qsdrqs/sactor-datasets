#include <stdio.h>
int main(void)
{
	int A;
	int B;
	int C;
	
	scanf("%d %d %d",&A,&B,&C);
	
	if(1 <= A && B <= 500 && 1 <= C <= 1000){
	if(C <= B + A){
		printf("YES\n");
	}
	else{
		printf("NO\n");
	}
	}
	return(0);
}
