#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // initialize and read input
  int n, m, i, j;
  scanf(" %d %d", &n, &m);
  int *A = (int *) malloc(sizeof(int) * n * m);
  int *b = (int *) malloc(sizeof(int) * m); 
  int *c = (int *) malloc(sizeof(int) * n);
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      scanf(" %d", A+i*m+j);
  for (i = 0; i < m; i++)
    scanf(" %d", b+i);
  // compute
  for (i = 0; i < n; i++) {
    *(c+i) = 0;
    for (j = 0; j < m; j++)
      *(c+i) += *(A+m*i+j) * *(b+j);
    // print
    printf("%d\n", *(c+i));
  }
  return 0;
}

