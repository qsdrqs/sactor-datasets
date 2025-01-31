#include <stdio.h>

int main(void)
{
	int i,j,a,b,c[3000],d[3000];

	i=0;

	scanf("%d %d", &a, &b);

	while((a==0) && (b==0))
	{	
		if(a>b)
		{
			c[i]=b;
			d[i]=a;
		}
		else
		{
			c[i] = a;
			d[i] = b;
		}

		i++;
		scanf("%d %d", &a, &b);
	}

	for(j=0;j<i;j++)
	{
		printf("%d %d\n", c[j], d[j]);
	}

	return 0;
}