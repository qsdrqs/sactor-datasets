#include<stdio.h>
#define MAX 6879568
int fibonacci(int);
int F[MAX];
int main(){
  int n,sum;

  scanf("%d",&n);
  sum  = fibonacci(n);

  printf("%d \n",sum);

  return 0;
}

int fibonacci(int n){
  if(n == 0 || n == 1)return F[n] = 1;
  else return F[n] = fibonacci(n-2)+fibonacci(n-1);
}