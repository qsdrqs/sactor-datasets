#include <stdio.h>

int main(void){
     int t;
     while(~scanf("%d",&t))
          if(t<0 || t>=10) return 1;

     return 0;
}