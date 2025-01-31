#include<stdio.h>

int fib[44];

int fibo(int n){
  if(n == 0)
    return 1;
  if(n == 1)
    return 1;

  if(fib[n-1] != 0){
    return fib[n-1];
  }else{
    fib[n-1] = fibo(n-1)+fibo(n-2);
  }
  return fib[n-1];
}

int main(){
  int i, n, ans;

  scanf("%d", &n);

  if(n >= 0 && n <= 44){
    for(i = 0; i < n ; i++)
      fib[i] = 0;
    ans = fibo(n);
    printf("%d\n", ans);
  }
  
  return 0;
}

