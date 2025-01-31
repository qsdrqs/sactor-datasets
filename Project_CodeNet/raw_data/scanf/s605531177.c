#include<stdio.h>
int main(void)
{
  int count=0, max,mod,a,b;
  scanf("%d%d",&max,&mod);
  b=mod;
  if(mod!=0)
  {
    while(b<=max)
    {
      count=count+ (max/b)*(b-mod);
      a=(max/b)*b;
      while(a<=max)
      {
        if(a%b>=mod) count++;
        a++;
      }
      b++;
    }
  }
  else count=max*max;
  printf("%d",count);
  return 0;
}