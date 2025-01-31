#include<stdio.h>
#include<math.h>
const int inf = 1000000000;
int main(void){
  int n;
  char x[105],sum[105];
  
  scanf("%d", &n);
  for(int i=0;i<n;i++){
    scanf("%d",&x[i]);   
  }
    int l=x[0];int r=x[0];

  for(int i=0;i<n;i++){
    if(l>x){
      l=x[i];
    }
    if(r<x){
      r=x[i];
    }

  }

  int ans = inf;
  for(int i=l;i<=r;i++){
     int cost = 0;

    for(int j=0;j<n;j++) {
      cost +=(x[j]-i)*(x[j]-i);
    }
    if(ans>cost){
      ans = cost;
      //ans = MIN(ans,cost);
    }
    
  }

  
  printf("%d", ans);
  return 0;
}