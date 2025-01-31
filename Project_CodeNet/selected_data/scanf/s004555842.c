#include <stdio.h>
#include <string.h>

int main(void)
{
 int a=0,b=0,i;
 char c[20];
 scanf("%s",c);
 for(i=0;i<20;i++){
  if(c[i]=='o'){
   a ++;
  }else if(c[i]=='x'){
   b++;
  }
 }
 if(b<8){
  printf("YES");
 }else{
  printf("NO");
 }
 return 0;
}
