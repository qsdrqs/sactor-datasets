#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define ll long long
#define rep(i,n) for(ll i=0;i<(n);i++)
#define max(p,q) ((p)>(q)?(p):(q))
#define min(p,q) ((p)<(q)?(p):(q))
#define chmax(a,b) ((a)=(a)>(b)?(a):(b))
#define chmin(a,b) ((a)=(a)<(b)?(a):(b))
#define abs(p) ((p)>=(0)?(p):(-(p)))
#define MOD 1000000007
ll powll(ll a,ll b){ll r=1;rep(i,b){r*=a;}return r;}
#define swap(a,b) do{ll w=(a);(a)=(b);(b)=w;}while(0)
#define swapd(a,b) do{double w=(a);(a)=(b);(b)=w}while(0)
#define in(a) scanf("%lld", &(a))
#define in2(a,b) scanf("%lld %lld",&(a),&(b))
#define in3(a,b,c) scanf("%lld %lld %lld",&(a),&(b),&(c))
#define ind(a) scanf("%lf", &(a))
#define ins(a) scanf("%s", (a))
#define inc(a) scanf("%c", &(a))
#define put(a) printf("%lld\n", (a))
#define putd(a) printf("%.15f\n", (a))
//      puts(a) printf("%s\n", a) 文字はこっち
//your code here!
int main(void){
    char X[200100];
    ins(X);
    //後ろからなめる
    //Sが表れかつ左にTが存在すれば-2
    ll ans=strlen(X), T=0, N=strlen(X);
    rep(i, N){
        if(X[N-1-i]=='T') T++;
        else if(T) ans -= 2;
    }
    put(ans);
    return 0;
}
