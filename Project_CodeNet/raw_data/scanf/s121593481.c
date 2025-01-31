#include<stdio.h>
int main(void){
    int a,b,menseki,nagasa;
    scanf("%d%d",&a,&b);
    menseki = a*b;
    nagasa = 2*(a+b);
    printf("%d %d\n",menseki,nagasa);
    return 0;
}