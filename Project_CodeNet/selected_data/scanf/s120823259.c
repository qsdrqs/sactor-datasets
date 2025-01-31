#include<stdio.h>

int main(){
  int a,b,h,i,j,k;
  char op;
 while(1){
    scanf("%d %c %d",&a,&op,&b);
    h=a+b;
    i=a-b;
    j=a*b;
    k=a/b;
    if(op == '?'){
      break;
    }
    else if(op == '+'){
      printf("%d\n",h);
    }
    else if(op == '-'){
      printf("%d\n",i);
    }
    else if(op == '*'){
      printf("%d\n",j);
    }
    else if(op == '/'){
      printf("%d\n",k);
    }
  }
  return 0;
}
