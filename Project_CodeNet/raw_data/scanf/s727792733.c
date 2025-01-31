#include<stdio.h>

int main(){
  int N,ans=0;
  scanf("%d",&N);
  int p[100],a[100]={};
  for(int i=0;i<N;i++){
    scanf("%d",&p[i]);
    a[i]=i+1;
    
  }
  for(int i=0;i<N;i++){
    if(a[i]!=p[i]){
      ans+=1;
    }
  }
  if(ans<3){
    printf("YES");
  }
  else{
    printf("NO");
  }
  return 0;
}