#include <stdio.h>
#include <stdlib.h>
#define max 2*100000

int bossy(int x,int n,int boss[])
{
    int j,dabang=0;

    for(j=1;j<n;j++)
    {
        if(boss[j]==x)dabang++;
    }
    printf("%d ",j);
    return dabang;
}
int main()
{
   int n,i,boss[max];
   scanf("%d",&n);
   for(i=1;i<n;i++)
   {
       scanf("%d",&boss[i]);
   }
   for(i=1;i<=n;i++)
   {
       printf("%d\n",bossy(i,n,boss));
   }
    return 0;
}