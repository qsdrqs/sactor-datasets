#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100

void initialize(void);
int isEmpty(void);
int isFull(void);
int push(int);
int pop(void);

int top;
int S[MAX];

int main(){
  int x,a,b;
  char s[100];

  initialize();

  while( scanf("%s", s) != EOF ){
    if ( s[0] == '+' ){
      a = pop();
      b = pop();
      push(b+a);
    } else if ( s[0] == '-' ){
      a = pop();
      b = pop();
      push(b-a);
    } else if ( s[0] == '*' ){
      a=pop();
      b=pop();
      push(b*a);
    } else {
      x = atoi(s);
      push(x);
    }
  }

  printf("%d\n",pop());

  return 0;
}

void initialize(void){
  top = 0;
}

int isEmpty(void){

  if(top == 0){
    return 1;
  }
  else return 0;
}

int isFull(void){

  if(top > MAX - 1){
    return 1;
  }
  else return 0;
}
int push(int x){

  if(isFull()){
    fprintf(stderr,"Overflow\n");
    exit(1);  
  }
  top++;
  S[top] = x;
}

int pop(){
  if(isEmpty()){
    fprintf(stderr,"Underflow\n");
    exit(2);
  }
  top--;
  return S[top+1];
}