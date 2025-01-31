#include <stdio.h>

void call(int n)
{
 int i,x;
 for (i = 1; i <= n; i++)
 {
  x = i;
  while (x) {
   if (i % 3 == 0) {
    printf(" %d", i);
    break;
   }
   if (x % 10 == 3) {
    printf(" %d", i);
    break;
   }
   x /= 10;
  }
 }
 printf("\n");
 return;
}
int main(void)
{
 int n;
 scanf("%d",&n);
 call(n);
 return 0;
}
