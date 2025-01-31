#include <stdio.h>
#include <stdlib.h>

int main(){
  unsigned short *A, *B;
  int C[10000 +1];
  int n, i, j;
  scanf("%d", &n);
  A = malloc(sizeof(short)*n+1);
  B = malloc(sizeof(short)*n+1);
  /* your code */
  for(i=0;i<n;i++){
    scanf("%d",&A[i]);
  }
  for(i=0;i<=10000;i++){
    C[i]=0;
  }
  for(j=1;j<=n;j++){
    C[A[j]]++;
  }
  for(i=1;i<10000;i++){
    C[i]=C[i]+C[i-1];
  }
  for(j=n;j>=1;j--){
    B[C[A[j]]]=A[j];
    C[A[j]]--;
  }
  for(i=1;i<n;i++){
    printf("%d ",B[i]);
  }
  printf("%d\n",B[n]);
  return 0;
}
