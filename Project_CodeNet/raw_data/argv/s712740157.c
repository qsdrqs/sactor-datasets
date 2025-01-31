#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
  
  	int X = atoi(argv[1]);
  	int Y = atoi(argv[2]);
  	int Z = atoi(argv[3]);
  
  int tmp;
  
  tmp = X;
  X = Y;
  Y = tmp;
  
  tmp = X;
  X = Z;
  Z = tmp;
  
  printf("%d","%d","%d",X,Y,Z);
  
  return 0;
  
  
  
}