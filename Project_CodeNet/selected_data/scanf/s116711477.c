#include <stdio.h>

int main(void) {
 int N = 0;
 int a[100000] = { 0 };
 unsigned long int ans = 1;
 scanf("%d", &N);
 for (int i = 0; i < N; i++) {
  scanf("%d", &a[i]);
  if (a[i] == 0) {
   printf("0");
   return 0;
  }
 }
 for (int i = 0; i < N; i++) {
  if (ans > 1000000000000000000) {
   printf("-1");
   return 0;
  }
  ans = ans * a[i];
 }
 printf("%ld", ans);
 return 0;
}
