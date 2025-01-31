#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  int r;
  int result;
  r = atoi(argv[1]);
  result = (r * r );
  printf("%d\n",result);
}
