#include <stdio.h>

/* 選択ソート (0オリジン) */
int selectionSort(int A[], int N) {
  int i, j, t, sw = 0, mini;
  for(i=0; i<N-1; i++) {
    mini = i;
    for(j=i; j<N; j++) {
      if(A[j] < A[mini]) mini = j;
    }

  	t = A[i];
  	A[i] = A[mini];
  	A[mini] = t;

  	if(i != mini) sw++;
  }
  return sw;
}

int main(void) {
  int A[100], N, i, sw;
  scanf("%d", &N);
  for(i=0;i<N;i++) scanf("%d",&A[i]);

  sw = selectionSort(A,N);

  for(i=0;i<N;i++) {
    if(i>0) printf(" ");
    printf("%d",A[i]);
  }
  printf("\n");
  printf("%d\n", sw);

  return 0;
}
