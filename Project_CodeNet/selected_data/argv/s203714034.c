#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int A = atoi(argv[1]), B = atoi(argv[2]), Answer = -1;
  if(A == B){
   Answer = A + B;
  }else if(A < B){
   Answer = B;
    B--;
    if(A == B){
      Answer += A;
    }else if(A < B){
      Answer += B;
    }else{
      Answer += A;
    }
  }else{
   Answer = A;
    A--;
    if(A == B){
      Answer += A;
    }else if(A < B){
      Answer += B;
    }else{
      Answer += A;
    }
  }
  printf("%d\n", Answer);
  return 0;
}
