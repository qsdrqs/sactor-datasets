#include<stdio.h>
int main()
{
	int H = 1, W = 1, i, j;

	while(1)
	{
		scanf("%d %d", &H, &W);
		if(H == 0 && W == 0)break;
	
		for(i=0; i<H; i++)
		{
			for(j=0; j<W; j++)
			{
				printf("#");
			}
		
			printf("\n");
		}
		printf("\n");
		
	}

	return 0;
}