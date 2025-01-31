#include<stdio.h>
int main(){
  int X,N,a,i,p[N];
  
  scanf("%d",&X);
  scanf("%d",&N);
  
  for(i=1;i<=N;i++)
    scanf("%d",&p[i]);
  
  
  for(i=1;i<=N;i++){
    a=p[i];
    if(X-p[i]>X-p[i+1]){
      a=p[i+1];
    }
      else if(X-p[i]==X-p[i+1]){
        if(p[i]<p[i+1]){
          a=p[i];
        }else{
          a=p[i+1];
        }
    }else if(i==N){
      printf("%d",a);
  }
  }
    return 0;
  }
