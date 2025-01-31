#include<stdio.h>

long long int min(long long int x, long long int y){
  long long int z;
  if(x < y){
    z = x;
  }else{
    z = y;
  }
  return z;
}
int main(){
  long long int win = 0;
  int n;
  scanf("%d", &n);
  long long int a[n+1];
  int i;
  for(i = 0; i < n+1; i++){
    scanf("%lld", &a[i]);
  }
  long long int b;
  for(i = 0; i < n; i++){
    scanf("%lld", &b);
    long long int tmp1 = min(b, a[i]);
    long long int tmp2 = min(a[i+1], b - tmp1);
    a[i+1] -= tmp2;
    win += (tmp1 + tmp2);
  }
  printf("%lld", win);
  return 0;
}
