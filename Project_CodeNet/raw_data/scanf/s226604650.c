#include <stdio.h>

int main(void)
{
 int a, b, c;
 
 scanf("%d", &a);
 scanf("%d", &b);
 scanf("%d", &c);
 
 int max = a;
 if (b > max) max = b;
 if (c > max) max = c;
 
 printf("%d\n", a + b+ c- max);
 
 return 0;
 
}