#include<stdio.h>
int main(void){
  int hpA,hpC;
  int atB,atD;
  
  scanf("%d",&hpA);
  scanf("%d",&atB);
  scanf("%d",&hpC);
  scanf("%d",&atD);
  
  do{
    hpC=hpC-atB;
    hpA=hpA-atD;
  }while(hpC>0&&hpA>0);
  
  if(hpA<=0){
    printf("No");
  }
  else{
    printf("Yes");
  }
  return 0;
}
  
  
  
    