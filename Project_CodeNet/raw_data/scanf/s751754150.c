#include<stdio.h>

int main(){
  int H,i;
  int A[250+1];
  
  scanf("%d",&H);
  for( i=1 ; i<=H ; i++ )
    scanf("%d",&A[i]);

  for( i=1 ; i<=H ; i++ ){
    printf("mode %d: key = %d, ",i,A[i]);
    if(i/2>0) printf("parent key = %d, ",A[i/2]);
    if(2*i<=H) printf("left key = %d, ",A[2*i]);
    if((2*i+1)<=H) printf("right key = %d, ",A[2*i+1]);
    printf("\n");
  }

  return 0;
}