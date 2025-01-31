#include <stdio.h>

int main(void)
{
  unsigned long a, b, sum;
  unsigned long k;

  scanf("%lu %lu %lu", &a, &b, &k);

  sum = a + b - k;
  if(sum > b) a = sum - b;
  else a = 0;
  b = sum;

  printf("%lu %lu\n", a, b);

  return 0;
}
