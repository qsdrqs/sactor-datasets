#include <stdio.h>

void merge(int*, int, int, int);
void mergeSort(int*, int, int);

int A[500000], n;
int count=0;

int main()
{
  
  int i;
  
  scanf("%d",&n);
  for(i=0; i<n; i++){
    scanf("%d",&A[i]);
  }

  mergeSort(A,0,n);

  for(i=0; i<n; i++){
    printf("%d",A[i]);
    if(i<n-1) printf(" ");
  }
  printf("\n%d\n",count);
  return 0;
}

  int L[500000], R[500000];
void merge(int *A, int left, int mid, int right){

  int k, n1, n2, i, j;
  
  n1 = mid - left;
  n2 = right - mid;
  for(i=0; i<=n1-1; i++) L[i] = A[left + i];
  for(i=0; i<=n2-1; i++) R[i] = A[mid + i];
  L[n1] = 1000000000;
  R[n2] = 1000000000;
  i = 0;
  j = 0;
  for(k=left; k<=right-1; k++){
    if(L[i]<=R[j]){
      A[k] = L[i];
      i = i + 1;
    }
    else{
      A[k]=R[j];
      j = j + 1;
    }
  count++;
  }
}
	

void mergeSort(int *A, int left, int right){

  int mid;
  
  if(left+1 < right){
    mid = (left + right)/2;
    mergeSort(A, left, mid);
    mergeSort(A, mid, right);
    merge(A, left, mid, right);
  }
}