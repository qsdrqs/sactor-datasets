#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int upll(const void*a, const void*b){return*(long long*)a<*(long long*)b?-1:*(long long*)a>*(long long*)b?1:0;}
int downll(const void*a, const void*b){return*(long long*)a<*(long long*)b?1:*(long long*)a>*(long long*)b?-1:0;}
void sortup(long long*a,int n){qsort(a,n,sizeof(long long),upll);}
void sortdown(long long*a,int n){qsort(a,n,sizeof(long long),downll);}
long long pom(long long a,long long n,int m){long long x=1;for(a%=m;n;n/=2)n&1?x=x*a%m:0,a=a*a%m;return x;}
long long gcd(long long p,long long q){
 while(q){
  long long t=p%q;
  p=q;
  q=t;
 }
 return p;
}
//#define MOD 998244353
long long a[100010];
long long dp1[100010],dp2[100010];
long long n;
int main(){
 scanf("%lld",&n);
 for(long long i=(0);i<(n);i++)scanf("%lld",a+i);
 dp1[0]=0;
 dp2[0]=0;
 for(long long i=(1);i<(n+1);i++){
  dp1[i]=gcd(dp1[i-1],a[i-1]);
  dp2[i]=gcd(dp2[i-1],a[n-i]);
 }
 long long ans=((dp1[n-1])>(dp2[n-1])?(dp1[n-1]):(dp2[n-1]));
 for(long long i=(1);i<(n-1);i++)ans=((ans)>(gcd(dp1[i],dp2[n-1-i]))?(ans):(gcd(dp1[i],dp2[n-1-i])));
 printf("%lld",ans);
}
