#include <stdio.h>

int main(void)
{
	int n;
	int sum;
	int temp;
	int i;
	
	while (1){
		scanf("%d", &n);
		
		if (n == 0){
			break;
		}
		
		sum = 0;
		for (i = 0; i < n / 4; i++){
			scanf("%d", &temp);
			sum += temp;
		}
		printf("%d\n", sum);
	}
	return (0);
}