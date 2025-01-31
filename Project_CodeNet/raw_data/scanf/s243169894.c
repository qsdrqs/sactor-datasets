#include<stdio.h>
#include<stdlib.h>

int main(){
  int i,j,n,R[200000],minv,maxv=-1;

  scanf("%d",&n);
 
  for(i=0;i<n;i++){
    scanf("%d",&R[i]);
    if(R[i]<1 || R[i]>1000000000){
      exit(8);
    }
  }

  minv=R[0];

  for(j=1;j<n-1;j++){
    if(maxv<R[j]-minv){
      maxv=R[j]-minv;
    }else if(maxv>R[j]-minv){
      maxv=maxv;
    }

    if(minv>R[j]){
      minv=R[j];
    }else if(minv<R[j]){
      minv=minv;
    }
  }

  printf("%d\n",maxv);

  return 0;
}