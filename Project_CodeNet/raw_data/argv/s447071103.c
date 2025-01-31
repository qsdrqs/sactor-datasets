#include <stdio.h>

int	main(int argc, char *argv[])
{
	int x;
	int ans;
	
	if(2 == argc)
	{
		x = (argv[1][0]) - 48;
		ans = x + (x * x) + (x * x * x);
	}
	printf("%d",ans);
}