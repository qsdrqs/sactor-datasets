#include <stdio.h>
int main(){
  int n,S[99],q,T[99],i,sc,tc,C = 0;
  scanf("%d",&n);
  for(i = 0;i < n;i++){
    scanf("%d",&S[i]);
  }
  scanf("%d",&q);
  for(i = 0;i < q;i++){
    scanf("%d",&T[i]);
  }
  for(sc = 0;sc < n;sc++){
    for(tc = 0;tc < q;tc++){
      if(S[sc] == T[tc]) C++;
    }
  }
  printf("%d",C);
  return 0;
}