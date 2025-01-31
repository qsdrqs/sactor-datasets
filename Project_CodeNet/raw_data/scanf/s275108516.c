#include <stdio.h>

int main()
{
	long long int n,d,k;
	scanf("%lld%lld%lld",&n,&k,&d);
	if(n<0){n*=(-1);}
	
	int a=k>(n/d)?(n/d):k;
	
	k-=a;
	n-=a*d;
	
	if(k%2==0){
		printf("%lld",n);
	}else{
		printf("%lld",d-n);
	}
}