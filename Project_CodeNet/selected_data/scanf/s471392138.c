#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
 int n;
 char **s;
 int num;
 scanf("%d", &n);
 s = malloc(n * sizeof(char*));
 for(int i=0; i<n; i++){
  s[i]=malloc(11*sizeof(char));
  for(int j=0;j<11;j++){
   s[i][j]=0;
  }
 }
 num = 0;
 for(int i=0; i<n; i++){
  char tmp[11];
  scanf("%s", tmp);
  for(int j=0; j<=i; j++){
   if (strcmp(tmp, s[j])==0){
    break;
   }
   if (num == j){
    strcpy(s[num], tmp);
    num++;
    break;
   }
  }
 }
 printf("%d", num);
 return (0);
}
