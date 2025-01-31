#include<stdio.h>
int main(void){
int a,b,c,n,i;
scanf("%d %d %d",&a,&b,&c);
n=0;
for(i=a;i<=b;i++){
if(c%i==0) n++;
}
printf("%d\n",n);
return 0;
}