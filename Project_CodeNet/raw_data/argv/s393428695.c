#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if(argc != 3)
    exit(0);
  
  int a = atoi(argv[1]);
  int b = atoi(argv[2]);
  
  if((a*b)&0b1 == 1)
    printf("Odd\n");
  else
    printf("Even\n");
  
  return 0;
}