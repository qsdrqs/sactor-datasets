#include <stdio.h>

int square(int);

int main(){

  int x;

  scanf("%d", &x);

  printf("%d\n", square(x));

  return 0;
}

int square(int a){

  int b = a*a*a;

  return b;
}
