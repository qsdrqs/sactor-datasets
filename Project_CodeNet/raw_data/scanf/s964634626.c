#include<stdio.h>
int main(){
  long long n,m;
  scanf("%lld%lld",&n,&m);
  if(n*m==1)
    printf("1\n");
  else if(n==1 || m==1)
    printf("%lld\n",n*m-2);
  else
    printf("%lld\n",(n-2)*(m-2));
  return 0;
}
