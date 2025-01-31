#include<stdio.h>

int main()
{
 char furui[50000];
 int n=2,i,input,ans;
 for(i=0;i<50000;i++)
 {
  furui[i]=1;
 }
 furui[0]=0;
 while(n<=50000)
 {
  if(furui[n-1]==1)
  {
   for(i=n*2;i<=50000;i+=n)
   {
    furui[i-1]=0;
   }
  }
  n++;
 }
 while(1)
 {
  scanf("%d",&input);
  if(input==0)break;
  ans=0;
  if(input%2==0)
  {
   for(i=1;i<input/2;i++)
   {
    if(furui[i-1]==1)
    {
     if(furui[input-i-1]==1)
     {
      ans++;
     }
    }
   }
  }
  printf("%d\n",ans);
 }
 return 0;
}
