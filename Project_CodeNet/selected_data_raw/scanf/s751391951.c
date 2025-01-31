#include<stdio.h>
#include<string.h>
int main(){
  int ans=0;
  char s[4];
  scanf("%s",s);
  if(s[0]=='M'){
    ans=6;
  }
  else if(s[0]=='T'){
    if(s[1]=='U'){
      ans=5;
    }
    else{
      ans=3;
    }
  }
  else if(s[0]=='W'){
    ans=4;
  }
  else if(s[0]=='F'){
    ans=2;
  }
  else if(s[0]=='S'){
    if(s[1]=='A'){
      ans=1;
    }
    else{
      ans=7;
    }
  }

  printf("%d\n",ans);
  return 0;
}