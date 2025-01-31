#include<stdio.h>
#include<stdlib.h>

int fib(int n){
  return n<2?1:fib(n-1)+fib(n-2);
}
int main(int argc, char *argv[]){
  int n = atoi(argv[1]);
  printf("%d\n",fib(n));
  return 0;
}
