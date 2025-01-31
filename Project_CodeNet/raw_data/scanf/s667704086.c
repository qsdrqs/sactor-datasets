#include <stdio.h>
int main(void){
  int n,a,max=0,sum=0,i;
  scanf("%d",&n);
  for(i=0; i<n; i++){
    scanf("%d",&a);
    if(a>max) max=a;
    sum+=a;
  }
  printf("%d\n",sum-max/2);
  return 0;
}
