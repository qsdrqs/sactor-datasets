#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int i;

	i = atoi(argv[2]);
	while (i < atoi(argv[3]))
	{
		if (i % atoi(argv[1]) == 0)
			printf("OK");
		i++;
	}
	printf("NG");
}