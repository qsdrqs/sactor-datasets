#include<stdio.h>

int main(){
  int i,j,n,m,S[10000],T[500],c=0,key;
  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%d",&S[i]);
  }
  scanf("%d",&m);
  for(i=0;i<n;i++){
    scanf("%d",&T[i]);
  }
  for(j=0;j<m;j++){
    S[n]=T[j];
    key=T[j];
    i=0;
    while(S[i]!=key){
      i++;
    }
    if(i!=n){
      c++;
    }
  }
  printf("%d\n",c);
  return 0;
}
