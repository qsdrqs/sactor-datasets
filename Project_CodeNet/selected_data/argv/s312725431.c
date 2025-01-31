#include <stdio.h>
#include <stdlib.h> 

int main(int argc,char *argv[]){
  int n = atoi(argv[1]);
  int a = atoi(argv[2]);
  int b = atoi(argv[3]);
  if(n*a<=b){
    printf("%d",n*a);
  }else{
    printf("%d",b);
  }
  return 0;
}
