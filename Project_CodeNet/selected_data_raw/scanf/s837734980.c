#include <stdio.h>

#define N 100

int main(){

  int i,j,min,count=0,num,kari,A[N];

  scanf("%d",&num);
  for(i=0; i<num; i++){
    scanf("%d",&A[i]);
  }

  for(i=0; i<num; i++){
    min = i;
    for(j=i; j<num; j++){
      if(A[j] < A[min]){
	min = j;
      }
    }
    if(A[min] != A[i]) count++;
	kari = A[min];
	A[min] = A[i];
	A[i] = kari;
  }

  for(i=0; i<num-1; i++)  printf("%d ",A[i]);
  printf("%d\n",A[num-1]);
  printf("%d\n",count);

  return 0;
}