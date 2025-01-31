#include <stdio.h>

int main(void)
{
	int gakuseki;
	float kg;
	float m;
	float bmi;
	
	while (scanf("%d, %f, %f", &gakuseki, &kg, &m) != EOF){
		if (bmi >= 25){
			printf("%d\n", gakuseki);
		}
	}
	return (0);
}