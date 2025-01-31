#include<stdio.h>

int main()
{
 int a,b,c,d;/*入力*/
 int ty=0,hg=0;
 while(scanf("%d,%d,%d",&a,&b,&c)!= (-1))
 {
  d=a*a+b*b;
  if(d==c*c)
  {
   if(a==b)
    hg++;
   else
    ty++;
  }
  else if(d>c*c)
  {
   if(a==b)
    hg++;
  }
 }
 printf("%d\n",ty);
 printf("%d\n",hg);
 return 0;
}
