#include <stdio.h>

int main(void){
int n,a,b,c,d,i=0;
scanf("%d",&n);
for(a=0;a<10;a++){
for(b=0;b<10;b++){
for(c=0;c<10;c++){
for(d=0;d<10;d++){
if(a+b+c+d==n){
i++;
}
}
}
}
}
printf("%d\n",i);
return 0;
}