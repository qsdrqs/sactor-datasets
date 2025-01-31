#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  int num, req, mul;
  int i;
  if(argc < 2)
    fprintf(stderr, "invalid inputs");
  num = atoi(argv[1]);
  req = atoi(argv[2]);
  if(num < 2)
    fprintf(stderr, "error");
  for(i = 1;;i++){
    if(i == 1)
      mul = num * i;
    else
      mul = num * i - 1;
    if(mul >= req){
      printf("%d\n", i);
      return 0;
    }else{
      continue;
    }
  }
}
