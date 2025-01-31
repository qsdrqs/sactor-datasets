#include <stdio.h>

#define rep(i, n) for (int i = 0; i < n; i = i + 1)
#define MAX 9223372036854775807
#define ARR_MAX 288199999999999999

void debug(char * string, long long int target) {
  printf("%s", string);
  printf("%lld", target);
  printf("%c", '\n');
}

long long a[100010];
int main() {
  int n;
  scanf("%d",&n);
  rep(i, n) {
    scanf("%lld",&a[i]);
  }

  int zero = 0;
  rep(i, n) {
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
  rep(i, n) {
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
