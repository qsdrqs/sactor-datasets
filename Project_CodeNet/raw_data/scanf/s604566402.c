#include <stdio.h>

int main(void){
	int n,d,x;

	scanf("%d %d",&n,&d);

	if(n%d == 0) x=0;
	else x=1;

	printf("%d",n/d + x);



	return 0;
}
