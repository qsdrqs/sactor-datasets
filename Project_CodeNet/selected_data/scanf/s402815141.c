#include <stdio.h>

void debug(char * string, long long int target) {
  printf("%s", string);
  printf("%lld", target);
  printf("%c", '\n');
}
long long a[100010];
int main() {
  int n;
  scanf("%d",&n);
  for (int i = 0; i < n; i = i + 1) {
    scanf("%lld",&a[i]);
  }
  int zero = 0;
  for (int i = 0; i < n; i = i + 1) {
    if (a[i]==0) {
      zero++;
    }
  }
  if (zero > 0) {
    //a[i] contains 0
    printf("0\n");
    return 0;
  }
  long long prod = 1;
  for (int i = 0; i < n; i = i + 1) {
    if (a[i] <= 1000000000000000000 / prod) {
      // This condition is equivalent to prod * a[i] <= 10^18
      prod*=a[i];
    } else {
      printf("-1\n");
      return 0;
    }
  }
  printf("%lld\n", prod);
  return 0;
}
