#include<stdio.h>
#include<stdlib.h>

int top,S[10000];

void push(int x){
  S[++top]=x;
}

int pop(){
  top--;
 return S[top+1];
}

int main(){
  int a,b;
  char s[1000];
  top=0;
  
  while(scanf("%s",s)!=EOF){
    if(s[0]=='+'){
      a=pop();
      b=pop();
      push(a+b);
    }else if(s[0]=='-'){
      a=pop();
      b=pop();
      push(a-b);
    }else if(s[0]=='*'){
      a=pop();
      b=pop();
      push(a*b);
    }else{
      push(atoi(s));
    }
  }
  printf("%d\n",pop());
  return 0;
}