#include<stdio.h>
int main(void){
	int N;
	scanf("%d",&N);
	if(N/10==9||N%10==9){
		printf("Yes\n");
	}
	else{
		printf("No\n");
	}
	return 0;
}