#include<stdio.h>

int insertionSort(int *A, int n){
  int i,j,v,k;
  for(i=0;i<n;i++) {
    if(i==n-1)printf("%d",A[i]);
    printf("%d ",A[i]);
  }
    printf("\n");
  for(i=1 ; i<n ; i++){
    v = A[i];
    j = i-1;
    while(j>=0 && A[j] > v){
      A[j+1] = A[j];
      j--;
    }
    A[j+1] = v;
    for(k=0;k<n;k++) {
      if(k==5) printf("%d",A[k]);
      printf("%d ", A[k]);
      }
    printf("\n");
  }
  return *A;
}
int main(){
  int i,j,n;
  int A[100];
  scanf("%d",&n);
  for(i=0 ; i<n ; i++) scanf("%d",&A[i]);
    insertionSort(A, n);
  return 0;
}
