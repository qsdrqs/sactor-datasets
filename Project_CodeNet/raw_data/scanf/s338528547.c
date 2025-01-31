#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//ABC165D
//ABC165C

int main(void) {
  long long n, k, i, cou=0, tmp, a, b;
  scanf(" %lld %lld %lld", &a, &b, &n);

  if(b>n){
    printf("%lld", a*n/b);
  }else{
    printf("%lld", a*(b-1)/b);
  }
  return 0;
}