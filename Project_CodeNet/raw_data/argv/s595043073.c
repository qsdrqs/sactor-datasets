#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{	
	char *a = argv[1];
	char *b = argv[2];
	char *c = argv[3];

	int turn = 1;

	while (1)
	{
		if (turn == 1)
		{
			if (*a == '\0')
			{
				write(1, "A", 1);
				return (0);
			}
			if (*a == 'b')
				turn = 2;
			if (*a == 'c')
				turn = 3;
			a++;
		}
		if (turn == 2)
		{
			if (*b == '\0')
			{
				write(1, "B", 1);
				return (0);
			}
			if (*b == 'a')
				turn = 1;
			if (*b == 'c')
				turn = 3;
			b++;
		}		
		if (turn == 3)
		{
			if (*c == '\0')
			{
				write(1, "C", 1);
				return (0);
			}
			else if (*c == 'a')
				turn = 1;
			else if (*c == 'b')
				turn = 2;
			c++;
		}
	}
	return (0);
}