#include<stdio.h>

int main(void)
{
  long long m,n,k,i,t;
  while(1)
    {
      i=0;
      k=1;
      scanf("%lld %lld",&m,&n);
      if(m==0 && n==0)break;
      if(m<n)
 {
   t=m;
   m=n;
   n=t;
 }
      while(k!=0)
 {
   k=m%n;
   m=n;
   n=k;
   i++;
 }
      printf("%lld %lld\n",m,i);
    }
  return 0;
}
