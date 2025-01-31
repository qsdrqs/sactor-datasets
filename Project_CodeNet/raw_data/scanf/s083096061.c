#include<stdio.h>

int main(void)
{
  double r, l, S;

  scanf("%lf", &r);

  l = 2 * r * 3.141592653589;
  S = r * r * 3.141592653589;
  
  printf("%lf %lf\n", S, l);

  return 0;
}

