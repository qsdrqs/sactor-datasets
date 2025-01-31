#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  int a[200000];
  int i, j, max=-999999;
  int n = atoi(argv[1]);
  for(i = 0; i < argc-2; i++){
    a[i] = atoi(argv[i+2]);
  }
  for(i = 0; i < n; i++){
    for(i = j+1; j < n; j++){
      if(max < (a[j]-a[i])){
        max = (a[j]-a[i]);
      }
    }
  }
  printf("%d\n", max);
  return 0;
}
