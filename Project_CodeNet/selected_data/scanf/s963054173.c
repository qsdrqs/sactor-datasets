#include <stdio.h>

int main(){
  int L=0, R=0;
  int i,j,K,mid,N1,N2,count=0;
  int num1[100000];
  int num2[50000];
  scanf("%d",&N1);
  for(i=0; i<N1; i++)
    scanf("%d",&num1[i]);
  scanf("%d",&N2);
  for(i=0; i<N2; i++)
    scanf("%d",&num2[i]);
  for(i=0; i<N2; i++){
    K = num2[i];
    L = 0;
    R = N1;
    while(L<R){
      mid = (L+R)/2;
      if(num1[mid] == K){ count++; break;}
      else if(K<num1[mid]) R=mid;
      else L = mid+1;
    }
  }
  printf("%d\n",count);
  return 0;
}
