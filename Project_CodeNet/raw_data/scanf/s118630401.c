#include<stdio.h>
#define m 200000
int main()
{
    int a[m],i,n,sum1=0,sum2=0,sum3=0;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        if(a[i]%4==0)
            sum1++;
        if(a[i]%2==0)
            sum2++;
    }
    sum3=n-sum2;
    if(sum2==n||(sum1>=sum3-1&&sum2==n-sum3))printf("Yes");
    else printf("No");
    return 0;
}
