#include<stdio.h>

int main(void){
  int i,L,n,m,sum,a,b;

  while(scanf("%d",&L),L){
    
    sum=0;
    for(i=1;i<=12;i++){
      scanf("%d %d",&m,&n);
      sum+=m-n;
      if(sum>=L)break;
    }
    
    if(sum<L)printf("NA\n");
    else printf("%d\n",i);

    if(i<12)
    for(i=12-i;i>0;i--)
      scanf("%d %d",a,b);
  }
  return 0;
}