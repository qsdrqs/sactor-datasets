#include <stdio.h>

void rec(int,int);

int n,q;
int A[20];
int M;

int flag=0;
int B[20];

int main(){
    
  int i,j;
  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%d",&A[i]);
  }
  scanf("%d",&q);
  for(j=0;j<q;j++){
    scanf("%d",&M);
    
    flag=0;
    rec(0,0);
    
    if ( flag == 1){
      printf("yes\n");
    }else{
      printf("no\n");
    }
  }
  
  return 0;
}

void rec(int a,int b){
  if(flag==1||b>M)return;
  if(a==n){
    if(b==M)flag=1;
  }else{
    rec(a+1,b+A[a]);
    rec(a+1,b);
  }
  
}