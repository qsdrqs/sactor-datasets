#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
 int a = atoi(argv[1]), b = atoi(argv[2]), c = atoi(argv[3]);
  if(a - b > 0 && c > 0){
    if(a - b >= c){
      c = 0;
    }else{
      c = c - (a-b);
    }
  }
  printf("%d\n",c);
}
