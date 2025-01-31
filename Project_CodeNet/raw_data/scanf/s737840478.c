#include <stdio.h>

int main(void)
{
	double x[4], y[4];
	int n;
	
	scanf("%d", &n);
	
	while (n){
		scanf("%lf.%lf %lf.%lf %lf.%lf %lf.%lf", &x[0], &y[0], &x[1], &y[1], &x[2], &y[2], &x[3], &y[3]);
		
		if ((y[1] - y[0]) / (x[1] - x[0]) == (y[3] - y[2]) / (x[3] - y[2])){
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}
		n--;
	}
	
	return (0);
}

		