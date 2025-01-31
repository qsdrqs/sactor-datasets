#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
 char *letter;
 char result[21];
 int length;
 int i, n, l;
 letter = argv[1];
 //printf("%s\n", argv[1]);
 // 文字数を調べる
 for(i=0; i<=21; i++){
  //printf("%c", letter[i]);
  if(letter[i] == '\0'){
   i -= 1;
   break;
  }
 }
 //
 l = 0;
 for(n=i; n>=0; n--){
  //printf("%c", letter[n]);
  result[l] = letter[n];
  l ++;
  //printf("%c", letter[n]);
 }
 result[l] = '\0';
 //printf("\n", result);
 printf("%s\n", result);
 return 0;
}
