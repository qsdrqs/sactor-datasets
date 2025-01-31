#include <stdio.h>
#include <string.h>

int main(){
  char s[1023]={'\0'};
  int i,sum;

  while(1){
    scanf("%s",s);
    if(strcmp(s,"0")==0) break;

    for(sum=0, i=0; i<1000 && s[i]!='\0' ; i++)
      sum+=s[i]-'0';

    printf("%d\n",sum);
  }
  return 0;
}