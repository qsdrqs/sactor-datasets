#include<stdio.h>
int main(){
int x,i,sum=0;
char ch[1001];
scanf("%d\n",&x);
while(1){
scanf("%s\n",&ch);
if(ch[0]=='0')break;
for(i=0;i<x;i++){
if(ch[i]=='1')sum+=1;
else if(ch[i]=='2')sum+=2;
else if(ch[i]=='3')sum+=3;
else if(ch[i]=='4')sum+=4;
else if(ch[i]=='5')sum+=5;
else if(ch[i]=='6')sum+=6;
else if(ch[i]=='7')sum+=7;
else if(ch[i]=='8')sum+=8;
else if(ch[i]=='9')sum+=9;
}
printf("%d\n",sum);
sum=0;
}
return 0;
}