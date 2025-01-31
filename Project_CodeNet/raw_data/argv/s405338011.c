#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  int n = atoi(argv[1]);
  int result = 0;

  result = (n*(1+n))/2;

  printf("%d\n", result);

  return 0;
}