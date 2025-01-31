#include<stdio.h>

int main(void){

  int x[10002],n,i;

  x[1]=2;
  for(i=2;i<=10000;i++)
    x[i]=i+x[i-1];
  
  while(scanf("%d",&n)!=EOF){
    printf("%d\n",x[n]);
  }
  return 0;
}