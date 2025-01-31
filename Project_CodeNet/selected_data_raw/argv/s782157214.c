//printf
#include <stdio.h>
//atoi
#include <stdlib.h>

int main(int argc,char* argv[]){
  int i,h,w;
  i = 0;
  if(argc != 3){
    printf("Argument must have height and width.\n");
    exit(1);
  }
  const int h_max = atoi(argv[1]);
  const int w_max = atoi(argv[2]);
  for(w=0;w<w_max;w++){
    for(h=0;h<h_max;h++){
      (w == 0 || w == (w_max - 1) || h == 0 || h == (h_max-1)) ? putchar('#') : putchar('.');
    }
    putchar('\n');
  }
  return 0;
}