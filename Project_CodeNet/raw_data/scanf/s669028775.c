#include<stdio.h>
int main(){
char ch[1001];
int i=0;

while(scanf("%c",&ch[i])!=EOF){
/*
if (ch[i]=='\n'){
printf("\n");
break;
}
*/
if (ch[i]<='Z' && ch[i]>='D'){
ch[i]-=3;
 printf("%c",ch);
}
if (ch[i]=='C') printf("Z");
if (ch[i]=='B') printf("Y");
if (ch[i]=='A') printf("X");
i++;
}
return 0;
}