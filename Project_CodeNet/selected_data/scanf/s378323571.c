#include<stdio.h>

int main()
{
    int n,k,t;
    scanf("%d %d",&n,&k);
    int ar[1000000];
    int flag;
    int count=0;
    for(int i=1;i<=n;i++)
    {
        flag=0;
        for(int j=1;j<=k;j++)
        {
            scanf("%d",&t);
            for(int z=0;z<t;z++)
            {
                scanf("%d",&ar[z]);
                if(ar[z]==i)
                    {
                        flag=1;
                    }
            }
        }
        if(flag==0)
        {
            count =count+1;
        }
    }
    printf("%d",count);
    return 0;
}
