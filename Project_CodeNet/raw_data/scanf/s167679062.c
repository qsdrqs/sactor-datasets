#include<stdio.h>
int main()
{
	int a,b,c,i,count=0;
	scanf("%d%d%d",&a,&b,&c);
	for(i=c;i>=c&&i<=b;i++)
	{
		if(i%a==0)
		{
			count++;
		}
	}
	printf("%d",count);
	return 0;
}