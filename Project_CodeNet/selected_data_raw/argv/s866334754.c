#include <stdio.h>

int varied(char *str)
{
	int i;
	int j;
	char temp;
	int flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (str[i] == str[j])
			{
				flag = 1;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	(void)argc;
	int res;

	res = varied(argv[1]);
	if (res == 1)
	{
		printf("no\n");
	}
	else if(res == 0)
	{
		printf("yes\n");
	}

}