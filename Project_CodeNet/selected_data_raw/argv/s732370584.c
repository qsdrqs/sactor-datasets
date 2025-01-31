#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	
	if (!(0 <= n && n <= 999) || argc != 2)
	{
		return 0;
	}

	int m = n % 10;

	if (m == 2 || m == 4 || m == 5 || m == 7 || m == 9)
	{
		printf("hon");
		return 0;
	}
	if (m == 0 || m == 1 || m == 6 || m == 8)
	{
		printf("pon");
		return 0;
	}
	if (m == 3)
	{
		printf("bon");
		return 0;
	}
	return 0;
}