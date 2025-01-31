#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv){
  int n1 = atoi(argv[1]);
  int n2 = atoi(argv[2]);
  int n3 = atoi(argv[3]);
  if(n1 == 5){
    if(n2 == 5){
      if(n3 == 7){
 printf("YES");
      }
      else{
 printf("NO");
      }
    }
    else if(n2 == 7 ){
      if ( n3 == 5){
 printf("YES");
      }
      else{
 printf("NO");
      }
    }
    else{
      printf("NO");
    }
  }
  if (n1 == 7 ){
    if(n2 == 5){
      if(n3 == 5){
 printf("YES");
      }
      else{
 printf("NO");
      }
    }
    else{
      printf("NO");
    }
  }
  return 0;
}
