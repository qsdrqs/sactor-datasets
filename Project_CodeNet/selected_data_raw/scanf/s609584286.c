#include <stdio.h>

int main(void){
	int i,n,sum=0,min,max,num;
	do{
		scanf("%d",&n);
	}while(n<1 || n>10000);

	for(i=0;i<n;i++){
		scanf("%d",&num);
		if(n==0){
			min=num;
			max=num;
		}
		if(num>=-1000000 && num<=1000000){
			sum+=num;
			if(num<min)
				min=num;
			if(num>max)
				max=num;
		}
	}
	printf("%d %d %d",min,max,sum);
	return 0;
}