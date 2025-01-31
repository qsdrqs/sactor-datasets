#include <stdio.h>
#include <stdlib.h>

int main(){
 int N = 0, W = 0, S = 0, E = 0, i;
 char *s = (char *)malloc(sizeof(char) * 1001);
 scanf("%s", s);
 for(i = 0; s[i] != '\0'; i++){
  if(s[i] == 'N'){
   N = 1;
  }
  else if(s[i] == 'W'){
   W = 1;
  }
  else if(s[i] == 'S'){
   S = 1;
  }
  else{
   E = 1;
  }
 }
//	printf("%d %d %d %d\n", N, W, S, E);
 if(N == S && W == E){
  printf("Yes\n");
 }
 else{
  printf("No\n");
 }
 return 0;
}
