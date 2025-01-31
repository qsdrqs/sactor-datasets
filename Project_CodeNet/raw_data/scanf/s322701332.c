#include<stdio.h>
int main(void){

int a,b,c,i,k=0;

scanf("%d %d %d",&a,&b,&c);

for(i=a;i<=b;i++){
if(i%c==0){
k=k+1;
}
}
printf("%d",k);

return 0;
}