#include <stdio.h>

int main(void){
 int tmp[30] = {0};
 int result[30] = {0};
 int a,b = 0;
 int i,j,k = 0;
 scanf("%d",&i);
 for(j = 0; j < i; j++){
  tmp[j] = j+1;
 }
 scanf("%d", &i);
 for( j = 0; j < i; j++ ){
  scanf("%d,%d", &a, &b);
  while(tmp[k] != 0){
   if(k+1 == a){
    result[k] = tmp[b-1];
   }
   else if(k+1 == b){
    result[k] = tmp[a-1];
   }
   else{
    result[k] = tmp[k];
   }
   k++;
  }
  k = 0;
  while( result[k] != 0 ){
   tmp[k] = result[k];
  }
 }
 for( i = 0; result[i] != 0; i++){
  printf("%d\n", result[i]);
 }
 return 0;
}
