#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>
typedef long long ll;
typedef long double ld;
#define rep(i,l,r)for(ll i=(l);i<(r);i++)
#define repp(i,l,r,k)for(ll i=(l);i<(r);i+=(k))
#define rrep(i,l,r)for(ll i=(l);i>=(r);i--)
#define INF (1LL<<60)
#define MOD1 1000000007
#define MOD2 998244353
#define MAX_N (1 << 17)
#define YES printf("Yes\n")
#define NO printf("No\n")
#define PN printf("\n")

void swap(ll *a, ll *b){ll c;c=*b;*b=*a;*a=c;}
ll max2(ll a,ll b){return a>=b?a:b;}
ll min2(ll a,ll b){return a>=b?b:a;}
ll min3(ll a, ll b, ll c){return (a<=b && a<=c) ? a : b<=c ? b : c;}
ll max3(ll a, ll b, ll c){return (a>=b && a>=c) ? a : b>=c ? b : c;}
ll minn(ll n, ll a[n]){ll b=INF;rep(i,0,n) b=min2(b,a[i]);return b;}
ll maxn(ll n, ll a[n]){ll b=-INF;rep(i,0,n) b=max2(b,a[i]);return b;}
ll ABS(ll a){return a>=0?a:(-a);}
ll POW(ll a, ll b){ll c=1;rep(i,0,b) c*=a;return c;}
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a,ll b){return a/gcd(a,b)*b;}
ll mod(ll n){return n%=MOD1;}
int upll(const void*a, const void*b){return*(ll*)a<*(ll*)b?-1:*(ll*)a>*(ll*)b?1:0;}
int downll(const void*a, const void*b){return*(ll*)a<*(ll*)b?1:*(ll*)a>*(ll*)b?-1:0;}
void sortup(ll*a,int n){qsort(a,n,sizeof(ll),upll);}
void sortdown(ll*a,int n){qsort(a,n,sizeof(ll),downll);}

typedef struct{ ll a , b;}fr;
int cmp1( const void *p, const void *q ) { return ((fr*)p) ->a - ((fr*)q)->a;}
int cmp2( const void *p, const void *q ) { return ((fr*)q) ->a - ((fr*)p)->a;}
void strsortup(fr*a,int n){qsort(a,n,sizeof(fr),cmp1);}
void strsortdown(fr*a,int n){qsort(a,n,sizeof(fr),cmp2);}

int main(void){
    char s[5000];
    ll n,ans=0;
    scanf("%lld%s",&n,s);
    ll r[n],g[n],b[n];
    r[n-1]=0; g[n-1]=0; b[n-1]=0;
    rrep(i,n-2,0){
        if(s[i+1]=='R') r[i]=r[i+1]+1;
        else r[i]=r[i+1];

        if(s[i+1]=='G') g[i]=g[i+1]+1;
        else g[i]=g[i+1];

        if(s[i+1]=='B') b[i]=b[i+1]+1;
        else b[i]=b[i+1];
    }

    rep(i,0,n-2){
        rep(j,i+1,n-1){
            if(s[i]==s[j]) continue;
            if(s[i]!='B' && s[j]!='B' ){
                ans+=b[j];
                if(2*j-i<n && s[2*j-i]=='B') ans--;
            }
            if(s[i]!='R' && s[j]!='R' ){
                ans+=r[j];
                if(2*j-i<n && s[2*j-i]=='R') ans--;
            }
            if(s[i]!='G' && s[j]!='G' ){
                ans+=g[j];
                if(2*j-i<n && s[2*j-i]=='G') ans--;
            }
        }
    }

    
    printf("%lld\n",ans);
    return 0;
}
