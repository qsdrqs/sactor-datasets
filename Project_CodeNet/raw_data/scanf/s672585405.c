#include<stdio.h>

int calc(int x){
    x=x*x*x;
    return x;
}

int main(void){
 int x;
 scanf("%d",&x);
 
 printf("%d\n",calc(x));

 return 0;
}

