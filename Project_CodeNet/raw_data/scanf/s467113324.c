#include <stdio.h> 
int main(void)
{
	int house[5][4][11] = { 0 };
	int n, i, j, k, a, b, c, d;
	scanf("%d", &n);
	for (n;n > 0;n--)
	{
		scanf("%d %d %d %d", &a, &b, &c, &d);
		house[a][b][c] += d;
	}
	for (i = 1;i < 5;i++)
	{
		for (j = 1;j < 4;j++)
		{
			for (k = 1;k < 11;k++)
			{
				printf("%d", house[i][j][k]);
			}
			printf("\n");
		}
		if (i == 4)
		{
			break;
		}
		printf("####################\n");
	}
	
	return 0;
}