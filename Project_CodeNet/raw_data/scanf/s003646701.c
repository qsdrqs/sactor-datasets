#include<stdio.h>
long long gcd(long long a,long long b){return b?gcd(b,a%b):a;}
long long lcm(long long a,long long b){return a*(b/gcd(a,b));}
int main(){
  int n;
  long long s=1,a,l=1,g=1;
  scanf("%d %lld",&n,&a);
  s=g=l=a;
  while(--n){
    scanf("%lld",&a);
    l=lcm(l,a);
    g=gcd(g,a);
    s*=a;
  }
  if(s==l)printf("pairwise coprime\n");
  else if(g==1)printf("setwise coprime\n");
  else printf("not coprime\n");
  return 0;
}
