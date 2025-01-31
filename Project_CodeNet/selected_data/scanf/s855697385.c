#include <stdio.h>

long long int yaku(long long int a,long long int b){
  if(a < b){
    long long int tmp = a;
    a = b;
    b = tmp;
  }
  long long int r = a % b;
  while(r > 0){
    a = b;
    b = r;
    r = a % b;
  }
  return b;
}
int main(){
  int n;
  scanf("%d",&n);
  long long int a[n];
  for(int i = 0;i < n;i++){
    scanf("%lld",&a[i]);
    if(i > 0){
      a[i] = a[i] / yaku(a[i],a[i - 1]) * a[i - 1];
    }
  }
  printf("%lld\n",a[n - 1]);
  return 0;
}
