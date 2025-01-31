#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  int A = atoi(argv[1]);
  int B = atoi(argv[2]);
  int C;
  C = A + B;
  if(C > 23){
    C = C - 24;
    printf("%d",C);
  }else{
    printf("%d",C);
  }
return 0;
}
