#include <stdio.h>

int main(void)
{
	int a=0;
	int b=0;
	scanf("%d %d",&a,&b);
	if(a<b){
		printf("a < b");
	}
	else if(a>b){
		printf("a > b");
	}
	else {
		printf("a == b");
	}
	printf("\n");
}