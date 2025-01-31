#include <stdio.h>

int main(){
 while(1){
 int a,b,kq;
 char x;
 scanf("%d %c %d", a,x,b);
 switch (x)
 {
 case '?':
  return 0;
  break;
 case '-':
  kq = a - b;
  break;
 case '+':
  kq = a + b;
  break;
 case '*':
  kq = a * b;
  break;
 case '/':
  kq = a / b;
  break;
 }
 printf("%d\n", kq);
 }
}
