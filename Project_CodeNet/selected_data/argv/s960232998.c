// BBQ Easy

#include<stdio.h>
#include<stdlib.h>

void exch(int *a, int *b);
void bsort(int *l, int len);
int min(int a, int b);
int main(int argc, char *argv[]) {
  int n, tmp, sum = 0;
  int *l;
  n = (int)argv[1];
  l = malloc(sizeof(int) * 2 * n);
  for(tmp = 2; tmp <= argc; tmp++) {
    l[tmp-2] = (int)argv[tmp];
  }
  bsort(l, n);
  for(tmp = 0; tmp <= n; tmp = tmp+2) {
    sum += l[tmp];
  }
  printf("%d\n", sum);
  return 0;
}
void exch(int *a, int *b) {
  *a = *a + *b;
  *b = *a - *b;
  *a = *a - *b;
}
void bsort(int *l, int len) {
  int i, j;
  for(i = 0; i < len; i++) {
    for(j = i+1; j < len; l++) {
      if(l[i] < l[j]) exch(l+i, l+j);
    }
  }
}
