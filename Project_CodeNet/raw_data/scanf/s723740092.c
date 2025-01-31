#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _max(_x, _y) ((_x)>(_y)?(_x):(_y))
#define _min(_x, _y) ((_x)>(_y)?(_y):(_x))

int main(void)
{
  int N, index, flg, count_dot, count_sharp;
  char S[200000];
  scanf("%d %s", &N, &S);
  //printf("N(%d) S(%s)\n", N, S);
  flg = 0;
  count_dot = 0;
  for (index = 0; index < N; ++index) {
    if (flg == 1 && S[index] == '.') {
      count_dot++;
      continue;
    }
    if (S[index] == '#') {
      flg = 1;
    }
  }
  
  flg = 0;
  count_sharp = 0;
  for (index = N-1; index >= 0; --index) {
    if (flg == 1 && S[index] == '#') {
      count_sharp++;
      continue;
    }
    if (S[index] == '.') {
      flg = 1;
    }
  }
  
  printf("%d\n", _min(count_dot, count_sharp));
  return 0;
}