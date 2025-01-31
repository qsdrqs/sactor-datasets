#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>
#include<ctype.h>

typedef long long ll;
typedef long double ld;
void swap(ll *a, ll *b){ll c;c=*b;*b=*a;*a= c;}
void cin(ll *n){ scanf("%lld",&(*n)); }
ll max2(ll a,ll b){return a>=b?a:b;}
ll min2(ll a,ll b){return a>=b?b:a;}
ll min3(ll a, ll b, ll c){return (a<=b && a<=c) ? a : b<=c ? b : c;}
ll max3(ll a, ll b, ll c){return (a>=b && a>=c) ? a : b>=c ? b : c;}
ll minn(ll n, ll a[]){ll b=(1LL<<60);for(ll i=(0);i<(n);i++) b=min2(b,a[i]);return b;}
ll maxn(ll n, ll a[]){ll b=-(1LL<<60);for(ll i=(0);i<(n);i++) b=max2(b,a[i]);return b;}
ll POW(ll a, ll b){ll c=1;for(ll i=(0);i<(b);i++) c*=a;return c;}
double POW_d(double a, double b){double c=1;for(ll i=(0);i<(b);i++) c*=a;return c;}
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a,ll b){return a/gcd(a,b)*b;}
ll mod_MOD1(ll n){n+= n<0?((-n)/1000000007 +1)*1000000007:0; return n%=1000000007;}
ll mod_p(ll n ,ll p){n+= n<0?((-n)/p+1)*p:0; return n%=p;}
ll change_into_num(char s[] , ll len, ll p){ return !p ? 0 : POW(10,p-1)*(s[len-p]-'0') + change_into_num(s,len,p-1); }
ll digits(ll a, ll b){return a/b?1+digits(a/b,b):1;}
ll base(ll n, ll a, ll i){return i==1?n%a:base(n/a,a,i-1);}
ll is_inArr1(ll x, ll n){ return ( x<0 || x>=n ) ? 0 : 1 ; }
ll is_inArr2(ll y, ll x, ll h, ll w){ return ( y<0 || y>=h || x<0 || x>=w ) ? 0 : 1 ; }
void lr_lower( int *l, int *r, ll am, ll val , int type ){ (type<3) ? ( am < val ? ( *l = (*l+*r)/2 ) : ( *r= (*l+*r)/2 ) ) : ( am <= val ? ( *l = (*l+*r)/2 ) : ( *r= (*l+*r)/2 ) ); }
void lr_upper( int *l, int *r, ll am, ll val , int type ){ (type<3) ? ( am <= val ? ( *l = (*l+*r)/2 ) : ( *r= (*l+*r)/2 ) ) : ( am < val ? ( *l = (*l+*r)/2 ) : ( *r= (*l+*r)/2 ) ); }
int cmp_lower( ll a, ll b, int type ){ return (type==1) ? ( a==b ? 1 : 0 ) : (type==2) ? ( a>=b ? 1 : 0 ) : ( a>b ? 1 : 0 ) ; }
int cmp_upper( ll a, ll b, int type ){ return (type==1) ? ( a==b ? 1 : 0 ) : (type==2) ? ( a<=b ? 1 : 0 ) : ( a<b ? 1 : 0 ) ; }
// return smallest p  which meets  a[p]==val :1  >=:2   >:3
ll lower_bound( ll a[], int l, int r, ll val , int type ){ while(r-l>1) lr_lower(&l,&r,a[ (l+r)/2 ],val,type); return cmp_lower(a[l],val,type) ? l : cmp_lower(a[r],val,type) ? r : -1; }
// return biggest p  which meets   a[p]==val :1  <=:2   <:3
ll upper_bound( ll a[], int l, int r, ll val , int type ){ while(r-l>1) lr_upper(&l,&r,a[ (l+r)/2 ],val,type); return cmp_upper(a[r],val,type) ? r : cmp_upper(a[l],val,type) ? l : -1; }
// count i  which meets ai==x
ll count(ll a[], int l, int r, ll x){ int p = lower_bound(a,l,r,x,1); return p==-1 ? 0 : upper_bound(a,p,r,x,1)-p+1; }
ll *factors[2] , fac_cnt=0 , is_factor_prepared=0;
ll factor_pre(){ for(ll i=(0);i<(1);i++){ if(is_factor_prepared++) return 0; } ll tmp=(1e6)/2+1, fac_tmp[tmp]; for(ll i=(0);i<(tmp);i++){fac_tmp[i]=i?2*i+1:2;} for(ll i=(1);i<(tmp);i++){if(fac_tmp[i]){ for(ll j=(3);j<(tmp/(2*i+1)+1);j+=(2)){ if( j*(2*i+1)<tmp ) fac_tmp[ (j*(2*i+1)-1)/2 ]=0; } }else continue;} for(ll i=(0);i<(tmp);i++){if(fac_tmp[i]){ for(ll j=(0);j<(2);j++){ factors[j] = realloc( factors[j] , sizeof(ll)*( fac_cnt +1 ) ); factors[j][j?fac_cnt++:fac_cnt]=j?0:fac_tmp[i]; } } } return 0; }
ll factor(ll n, ll new_common_plus){ factor_pre(); for(ll i=(0);i<(fac_cnt);i++){ ll cnt=0; for(ll j=(0);j<(1);j++){ while( ( cnt+= n %factors[0][i]==0 ? 1 : 0 ) && (n/=factors[0][i]) %factors[0][i]==0 ) continue; } factors[1][i]= new_common_plus==1 ? cnt : new_common_plus==2 ? max2(factors[1][i],cnt) : factors[1][i]+cnt ; if( factors[0][i]> n ) break; } return n; }
ll judge_prime(ll n){ factor_pre(); for(ll i=(0);i<(fac_cnt);i++){ if(n<factors[0][i]*factors[0][i] || n==factors[0][i]) break; else if(n%factors[0][i]==0) n/=n; } return n==1?0:1; }
ll *mf_arr,*inv_arr,*finv_arr,is_minv_made=0,is_mf_made=0,num_of_inv=2*1e6+10;
ll makeinv(ll n , ll mod){ for(ll i=(0);i<(1);i++){if(is_minv_made++) return 0;} inv_arr = realloc(inv_arr, sizeof(ll)*2 ); finv_arr = realloc(finv_arr, sizeof(ll)*2 ); inv_arr[1]=1;finv_arr[0]=finv_arr[1]=1; for(ll i=(2);i<(n+1);i++){ inv_arr = realloc(inv_arr, sizeof(ll)*(i+1) ); finv_arr = realloc(finv_arr, sizeof(ll)*(i+1) ); inv_arr[i]= mod - inv_arr[mod%i] * (mod / i) % mod; finv_arr[i] = finv_arr[i - 1] * inv_arr[i] % mod; } return 0; }
ll make_mf(ll n, ll mod){ for(ll i=(0);i<(1);i++){ if(is_mf_made++) return 0; } mf_arr = realloc(mf_arr, sizeof(ll)*2 ); ll x=1; mf_arr[0]=mf_arr[1]=x; for(ll i=(2);i<(n+1);i++){ x=x*i%mod; mf_arr = realloc(mf_arr, sizeof(ll)*(i+1) ); mf_arr[i]=x; } return 0; }
ll m_inv(ll x, ll mod, ll is_fac ){ makeinv(num_of_inv,mod); return is_fac?finv_arr[x]:inv_arr[x]; }
ll m_f(ll x, ll mod){ make_mf(num_of_inv,mod); return mf_arr[x]; }
ll mod_nck(ll n, ll k, ll mod){ return m_f(n,mod)*m_inv(k,mod,1)%mod*m_inv(n-k,mod,1)%mod; }
ll m_p(ll r,ll n,ll mod){ ll t=1,s=r; while(n>0){ t = (n&1) ? t*s%mod : t; s=s*s%mod; n>>=1; } return r?t:0; }
ll m_mul2(ll a, ll b, ll mod){ return a*b%mod; }
ll m_mul3(ll a, ll b, ll c, ll mod){ return m_mul2(a*b%mod,c,mod); }
ll m_mul4(ll a, ll b, ll c, ll d, ll mod){ return m_mul3(a*b%mod,c,d,mod); }
ll m_mul5(ll a, ll b, ll c, ll d, ll e, ll mod){ return m_mul4(a*b%mod,c,d,e,mod); }
int upll(const void*a, const void*b){return*(ll*)a<*(ll*)b?-1:*(ll*)a>*(ll*)b?1:0;}
int downll(const void*a, const void*b){return*(ll*)a<*(ll*)b?1:*(ll*)a>*(ll*)b?-1:0;}
int cmp_string( const void * a , const void * b ) { return strcmp( (char *)a , (char *)b ); } // qsort((void*)s,n,sizeof(s[0]),int_sort );
int cmp_char(const void * a, const void * b) { return *(char *)a - *(char *)b;}
void sortup(ll*a,int n){qsort(a,n,sizeof(ll),upll);}
void sortdown(ll*a,int n){qsort(a,n,sizeof(ll),downll);}
void sort_string(int n,int size,char s[][size]){ qsort( (void*)s , n , sizeof(s[0]) , cmp_string ); }
void sort_char(char *s){ qsort( (void *)s , strlen(s) , sizeof(char) , cmp_char ); }
ll unique_string(ll n ,ll size, char s[][size]){ ll ans=1; for(ll i=(1);i<(n);i++) if( strcmp(s[i],s[i-1]) ) ans++; return ans; }
ll unique_num(ll n , ll a[]){ ll ans=1; for(ll i=(1);i<(n);i++) if( a[i]!=a[i-1] ) ans++; return ans; }
typedef struct{ ll a , b;}fr;
int cmp1( const void *p, const void *q ) {
    if( ((fr*)p) ->b == ((fr*)q)->b ) return ((fr*)p) ->a - ((fr*)q)->a;
    return ((fr*)p) ->b - ((fr*)q)->b;}
int cmp2( const void *p, const void *q ) { return ((fr*)q) ->a - ((fr*)p)->a;}
void strsortup(fr*a,int n){qsort(a,n,sizeof(fr),cmp1);}
void strsortdown(fr*a,int n){qsort(a,n,sizeof(fr),cmp2);}
// char s[1151154];
ll dp[1151151];
int main(void){
    // fgets(s,sizeof(s),stdin); 
    ll n;
    // ll ans=0;
    cin(&n);
    // scanf("%s",s);
    fr a[n];
    for(ll i=(0);i<(n);i++){
        cin(&a[i].a);
        cin(&a[i].b);
    }
    strsortup(a,n);
    // rep(i,0,n) printf("%lld %lld\n",a[i].a,a[i].b);
    // ll p=0;
    // if(a[0].a<=a[0].b) dp[0]=1;
    for(ll i=(0);i<(n);i++){
        for(ll j=(n);j>=(1);j--){
            if(j-1&&!dp[j-1]) continue;
            if(dp[j]){
                if(dp[j]>dp[j-1]+a[i].a&&dp[j-1]+a[i].a<=a[i].b){
                    dp[j]=dp[j-1]+a[i].a;
                }
            }else{
                if(dp[j-1]+a[i].a<=a[i].b){
                    dp[j]=dp[j-1]+a[i].a;
                }
            }
        }
        // rep(j,0,n+1) printf("%lld ",dp[j]);
        // PN;
    }
    for(ll i=(n);i>=(0);i--){
        if(dp[i]||!i){
        printf("%lld\n",i); break;
        }
    }
    // printf("%lld\n",dp[n]);
    return 0;
}
