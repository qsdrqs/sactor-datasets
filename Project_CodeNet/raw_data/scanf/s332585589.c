#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ll long long
#define rep(i,l,r)for(ll i=(l);i<(r);i++)
#define repp(i,l,r,k)for(ll i=(l);i<(r);i+=(k))
#define INF ((1LL<<62)-(1LL<<31))
#define max(p,q)((p)>(q)?(p):(q))
#define min(p,q)((p)<(q)?(p):(q))
#define bit(n,m)(((n)>>(m))&1)
int upll(const void*a, const void*b){return*(ll*)a<*(ll*)b?-1:*(ll*)a>*(ll*)b?1:0;}
int downll(const void*a, const void*b){return*(ll*)a<*(ll*)b?1:*(ll*)a>*(ll*)b?-1:0;}
void sortup(ll*a,int n){qsort(a,n,sizeof(ll),upll);}
void sortdown(ll*a,int n){qsort(a,n,sizeof(ll),downll);}
ll pom(ll a,ll n,int m){ll x=1;for(a%=m;n;n/=2)n&1?x=x*a%m:0,a=a*a%m;return x;}
ll gcd(ll p,ll q){
	while(q){
		ll t=p%q;
		p=q;
		q=t;
	}
	return p;
}
//#define MOD 998244353
#define MOD 1000000007
#define invp(a,p)pom(a,p-2,p)

ll a[100010];
ll dp1[100010],dp2[100010];
ll n;
int main(){
	scanf("%lld",&n);
	rep(i,0,n)scanf("%lld",a+i);
	dp1[0]=0;
	dp2[0]=0;
	rep(i,1,n+1){
		dp1[i]=gcd(dp1[i-1],a[i-1]);
		dp2[i]=gcd(dp2[i-1],a[n-i]);
	}
	ll ans=max(dp1[n-1],dp2[n-1]);
	rep(i,1,n-1)ans=max(ans,gcd(dp1[i],dp2[n-1-i]));
	printf("%lld",ans);
}