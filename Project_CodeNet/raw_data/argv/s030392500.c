#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int M=atoi(argv[1]), D=atoi(argv[2]);
  int i, j, cnt = 0, a;
  for(i=2; i<=M; i++) {
    for(j=22; j<=D; j++) {
      a = j%10;
      if(j%10 >= 2) {
        if(a*(j/10) == i){
          cnt++;
        }
      }
    }
  }
  printf("%d\n", cnt);
  return 0;
}
