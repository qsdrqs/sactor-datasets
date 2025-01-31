#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char **argv){
  if(argc = 0)
    fprintf(stderr, "no inputs\n");
  
  char *pre[3];
  char *real[3];
  char *p = argv[1];
  bool flag = false;
  int i = 0, count = 0;
  
  while(p >= argv[1]){
    if(p == "\n"){
      flag = true;
      i = 0;
      continue;
    }
    if(!(p == "S" || p == "C" || p == "R")){
		fprintf(stderr, "invalid inputs");
    }
    
    if(!flag){
      pre[i] = p;
    }else{
      real[i] = p;
    }
    
    i++;
  }
   
  for(int j = 0; j < 3; j++){
    if(pre[j] == real[j])
      count++;
    else
      continue;
  }
  
  printf("%d\n", count);
}
  
  
