#include <stdio.h>
int main(void)
{
	int n,max,tmp,count,cmax;
	scanf("%d\n",&n);
	max=1;
	for(int i=2;i<=n;++i)
	{
		count = 0;
		tmp = i;
		while(tmp%2==0)
		{
			tmp/=2;
			count++;
		}
		if(count>=cmax)
		{
			cmax=count;
			max=i;
		}
	}
	printf("%d\n",max);
}