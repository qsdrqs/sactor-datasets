#include<stdio.h>
#define max 50000
int main()
{
	char furui[max];
	int n=2,i,input,ans;
	
	for(i=0;i<max;i++)
	{
		furui[i]=1;
	}
	furui[0]=0;
	while(n<=max)
	{
		if(furui[n-1]==1)
		{
			for(i=n*2;i<=max;i+=n)
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