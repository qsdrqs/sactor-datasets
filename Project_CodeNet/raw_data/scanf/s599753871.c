#include <stdio.h>

int main (void)
{
	int a, b, c, cnt;
	
	while (scanf("%d %d", &a, &b) != EOF)
	{
		c = a+b;
		cnt = 0;
		while (c > 0)
		{
			c /= 10;
			cnt++;
		}
		
		printf("%d\n", cnt);
	}
	
	return 0;
}