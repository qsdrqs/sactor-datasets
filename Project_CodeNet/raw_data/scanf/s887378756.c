#include<stdio.h>
#define SIDES 2
int main(void){
        int a,b,S,L;

        scanf("%d%d",&a,&b);
        S = a * b;
        L = a*SIDES + b*SIDES;

        printf("%d %d\n",S,L);

        return 0;
}