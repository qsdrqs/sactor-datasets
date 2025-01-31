#include<stdio.h>
int main(void){
	int i,n;
	scanf("%d",&n);
	int array[100];
	for(i=0;i<n;i++){
		scanf("%d",&array[i]);
	}
	for(i=n-1;i>=0;i--){
		if(i==0){
			printf("%d\n",array[i]);
		}else {printf("%d ",array[i]);
		}
	}
	
	return 0;
}