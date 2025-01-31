#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
 int a=0, b=0;
  // printf("%d %s\n", argc,argv[argc]);
  for(int i = 0; i < 3; i++){
 if(argv[1][i] == 'A'){
    a++;
   }else if(argv[1][i] == 'B'){
    b++;
    }
  }
  if(a == 1 || b == 1)
 printf("Yes");
  else
    printf("No");
  return 0;
}
