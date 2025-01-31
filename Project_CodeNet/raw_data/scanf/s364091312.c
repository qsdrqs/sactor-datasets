#include<stdio.h>
    
    int min(long long a,long long b){
        if(a < b) return a;
        else return b;
    }

    int main(){
    	long long n,t,i,sum = 0;
    	scanf("%lld %lld",&n,&t);
        long long a[n];
    	for(i = 0;i < n;i++)
    	scanf("%lld",&a[i]);
    	for(i = 0;i < n;i++){
            sum += min(a[i+1] - a[i],t);
    	}
    	printf("%lld\n",sum);
    	
    }