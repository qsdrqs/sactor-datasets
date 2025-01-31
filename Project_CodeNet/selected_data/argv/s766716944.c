#include<stdio.h>
#include<string.h>

int main(int argc, char **argv){
  int i =0;
  if(argc != 4){
        //perror("argc");
    return 0;
  }
  if((strlen(argv[2])<1) || (strlen(argv[2])>100)){
    //perror("a");
   return 0;
  }
  if((argv[2][0]<'A') || (argv[2][0]>'Z')){
        //perror("b");
    return 0;
  }
  for(i=1; i<strlen(argv[2]); i++){
    if(argv[2][i]<'a' || argv[2][i]>'z'){
          //perror("c");
    return 0;
    }
  }
  printf("%c%c%c\n", argv[1][0], argv[2][0], argv[3][0]);
  return 0;
}
