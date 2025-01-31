#include<stdio.h>
#include<stdlib.h>

int partition(int A[],int p,int r){
  int x = A[r];
  int i = p - 1;
  int j,tmp;
  for(j=p;j<=r-1;j++){
    if(A[j] <= x){
      i++;
      tmp = A[i];
      A[i] = A[j];
      A[j] = tmp;
    }
  }
    tmp = A[i+1];
    A[i+1] = A[r];
    A[r] = tmp;
    return i+1;
}
int main(){
  int n,i,x;
  int *A;
  scanf("%d",&n);
  A = malloc(sizeof(int)*n);
  for(i=0;i<n;i++){
    scanf("%d",&A[i]);
  }
  x = partition(A,0,n-1);
  for(i=0;i<n;i++){
    if(i == x){
      printf("[%d]",A[i]);
    }else{
    printf("%d",A[i]);
    }
    if(i<n-1)printf(" ");
  }
  puts("");
  free(A);
  return 0;
}
