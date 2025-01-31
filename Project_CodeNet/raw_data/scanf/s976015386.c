#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

int main(){
  int i, j;

  scanf("%d %d", &i, &j);

  int plus;
  int minus;
  int div;
  plus = i + j;
  minus = i-j;
  div = i*j;
  int max = plus;
  if(max<minus){
    max = minus;
  }
  if(max < div){
    max = div;
  }
  printf("%d\n", max);
  return 0;
}
