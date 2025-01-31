#include <stdio.h>
#include <math.h>

int main(void)
{
	double r, s, l;

	scanf("%lf", &r);

	s = r * r * M_PI;
	l = 2 * r * M_PI;

	printf("%lf %lf\n", s, l);

	return 0;
}