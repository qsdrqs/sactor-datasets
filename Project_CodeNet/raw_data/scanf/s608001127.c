#include<stdio.h>
#include<stdlib.h>

int main(void){
  long long int n,k; scanf("%lld%lld",&n,&k);
  while(n>k/2){n = llabs(n-k);}
  printf("%lld",n);
  return 0;
}
