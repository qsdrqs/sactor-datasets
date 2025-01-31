#include<stdio.h>

int main(void){
	int a,b,c;
	int gcd,lcm;
	
	while(1){
		scanf("%d %d",&a,&b);
		c=a%b;
		for(c=a%b,gcd=b;c!=0;c=b%c){
			}
		lcm=a*b/gcd;
		printf("%d %d\n",gcd,lcm);
	}
	
	return 0;
}