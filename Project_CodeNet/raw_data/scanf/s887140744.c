#include <stdio.h>

int price[3];

int main(void){
   
   int i;
   
   printf(" a, b, cの値段はそれぞれ \n");
   
   for(i = 0;i < sizeof price/sizeof(int);i++){
     printf("￥");
     scanf("%d", &price[i]);  // num = Integer.parseInt(buf) とほぼ同等
   }
   
   printf("です。\n");
   
   int min = price[0] + price[1];
   
     if(price[0]+price[2] < price[0]+price[1]){
       min = price[0]+price[2];
     }
     if(price[1]+price[2] < price[0]+price[2]){
       min = price[1]+price[2];
     }
     
   printf("最安値は￥%dです。\n", min);
   
   return 1;
}