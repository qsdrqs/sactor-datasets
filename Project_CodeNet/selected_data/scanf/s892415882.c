#include<stdio.h>

int main(){
 int n,x;
 int i=1;
 scanf("%d", &n);
 while(++i <= n){
  x=i;
  if(x%3 == 0){
   printf(" %d", i);
  }else{
    x /=10;
   while(x){
    if(x%10 ==3){
     printf("%d", i);
     break;
    }
    x /=10;
   }
  }
 }
 return 0;
}
