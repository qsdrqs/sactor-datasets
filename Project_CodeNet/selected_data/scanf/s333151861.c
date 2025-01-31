//E - Dist Max
//Hiia
#include <stdio.h>
#include <stdlib.h>//rannsuu, zettaichi(absolute)
#include <time.h>
//srand((unsigned int) time(0));
#include <math.h>//koudona keisann
#include <string.h>//hairetsu

typedef long long ll;
//#define N 998244353
int gcd(int m,int n){if((0==m)||(0==n))return 0;while(m!=n)if(m>n)m=m-n;else n=n-m;return m;}
int lcm(int m,int n){if((0==m)||(0==n))return 0;return(m*n/gcd(m, n));}
int fact(int x){if(x==1) return(x);else return(x*fact(x-1));}//Kaijou x!
int ruijou(int base,int exponent){int i,answer=1;i=exponent;while(i!=0){answer=answer*base;--i;}return answer;}//ruijou base^exponent
long long int llgcd(long long int m,long long int n){if((0==m)||(0==n))return 0;while(m!=n)if(m>n)m=m-n;else n=n-m;return m;}
long long int lllcm(long long int m,long long int n){if((0==m)||(0==n))return 0;return(m*n/llgcd(m, n));}
long long int llfact(long long int x){if(x==1) return(x);else return(x*llfact(x-1));}//Kaijou
int llruijou(long long int base,long long int exponent){long long int i,answer=1;i=exponent;while(i!=0){answer=answer*base;--i;}return answer;}//ruijou base^exponent
int main()
{
  ll n,a[200010],b[200010],ans=0;
  scanf("%lld", &n);
  for(ll i = 1; i <= n; i++) {
    scanf("%lld %lld", &a[i], &b[i]);
  }
  for(ll i = 1; i < n; i++) {
    for(ll j = i+1; j <= n; j++) {
      ll tmp1,tmp2,tmp3;
      tmp1=a[i]-a[j];
      tmp2=b[i]-b[j];
      if(tmp1<0){
        tmp1*=(-1);
      }
      if(tmp2<0){
        tmp2*=(-1);
      }
      tmp3=tmp1+tmp2;
      ans=((tmp3)>(ans)?(tmp3):(ans));
    }
  }
  printf("%lld\n", (ans+1000000007)%1000000007);
  return 0;
}
