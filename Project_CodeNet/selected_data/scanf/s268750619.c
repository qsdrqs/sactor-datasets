#include<stdio.h>

int min(int a,int b){return (a>b)?b:a;}
int dp[1000000],dp_odd[1000000];
int main(){
  int i,j,n,tmp;
  int plc[1000],num;
  for(i=0;i<1000000;i++)dp[i] = dp_odd[i] = 1000000 +1;
  dp[0] = dp_odd[0] = 0;
  tmp = 1;
  for(num=1;;num++){
    plc[num] = tmp;
    tmp *= num+3; tmp /= num;
    if(tmp>=1000000)break;
  }
  for(i=0;i<1000000;i++){
    for(j=1;j<num;j++){
      if(i<plc[j])break;
      dp[i] = min(dp[i],dp[i-plc[j]]+1);
      if(plc[j]&1)dp_odd[i] = min(dp_odd[i],dp_odd[i-plc[j]]+1);
    }
  }
  while(scanf("%d",&n) && n)printf("%d %d\n",dp[n],dp_odd[n]);
}
