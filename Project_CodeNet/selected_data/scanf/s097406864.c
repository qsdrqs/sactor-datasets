#include <stdio.h>

int main() {
 int big[3]={0};
 int b=0;
 int i;
 for(i=0; i<10; i++){
  scanf("%d",&b);
  if(big[0]<b){
   big[2]=big[1];
   big[1]=big[0];
   big[0]=b;
  }else{
   if(big[1]<b){
    big[2]=big[1];
    big[1]=b;
   }else{
    if(big[2]<b){
     big[2]=b;
    }
   }
  }
 }
 printf("%d\n%d\n%d\n",big[0],big[1],big[2]);
 return 0;
}
