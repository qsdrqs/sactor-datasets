#include<stdio.h>

int main(){
  int n,q,m,i,j,b[128],w;
  while(scanf("%d%d",&n,&q),n!=0){
    for(i=0;i<128;i++){b[i]=0;}
    for(i=0;i<n;i++){
      scanf("%d",&m);
      for(j=0;j<m;j++){
        scanf("%d",&w);
        b[w]++;
      }
    }
    w=0;
    for(i=1;i<128;i++){
      if(b[w]<b[i]){w=i;}
    }
    if(b[w]<q){printf("0\n");}
    else{printf("%d\n",w);}
  }
  return 0;
}

