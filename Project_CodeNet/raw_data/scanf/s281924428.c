#include<stdio.h>

int main(){
  int n, i, max, min;
  int A[200000];

  scanf("%d",&n);

  for(i = 0; i < n; i++) scanf("%d",&A[i]);

  min = A[0];

  for(i = 1; i < n; i++){
    if(A[i] - min > max) max = A[i] - min;
    if(A[i] < min ) min = A[i];
  }

  printf("%d\n",max);

  return 0;
}