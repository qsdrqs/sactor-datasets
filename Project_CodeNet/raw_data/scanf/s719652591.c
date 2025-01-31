#include <stdio.h>
int data[100];
int w, i, p=1, s;



int main(){
 for(i = 0; i < 100; i++){
  scanf("%d", &data[i]);
  w = data[i];
  if(w == 0){
   i--;
  }
  p++;
  if(p == 100) break;
 }
 
 for(s = 0; s < i; s++){
  printf("%d\n", data[s]);
 }
}