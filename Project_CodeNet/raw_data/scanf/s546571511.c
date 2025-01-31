#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int i,j,n,prime[20000],twin,twins[20000];

int main(){
	for(i=2;i<10005;i++){prime[i]=1;}
	for(i=2;i<=10000;i++){
		if(prime[i]==1){
			for(j=i*i;j<=10000;j+=i)prime[j]=0;
			if(prime[i-2]==1)twin=i;
		}
		twins[i]=twin;
	}
	while(scanf("%d",&n)*n){
		printf("%d %d\n",twins[n]-2,twins[n]);
	}
	return 0;
}