#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
   int X = atoi(argv[0]);
   int Y = atoi(argv[1]);
   int Z = atoi(argv[2]);
  int tmp;
  tmp = X;
  X = Y;
  Y = tmp;
  tmp = X;
  X = Z;
  Z = tmp;
  printf("%d %d %d\n",X,Y,Z);
  return 0;
}
