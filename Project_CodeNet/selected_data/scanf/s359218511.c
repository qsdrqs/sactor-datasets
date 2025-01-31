#include<stdio.h>
#include<stdlib.h>

typedef long long int int64;
const int mod=1000000007;
int modPow(int r,int n){
  int t=1;
  int s=r;
  while(n>0){
    if(n&1) t=((int64)(t)*(s)%mod);
    s=((int64)(s)*(s)%mod);
    n>>=1;
  }
  return t;
}
void run(void){
  int n,c;
  scanf("%d%d",&n,&c);
  int *a=(int *)calloc(2*n,sizeof(int));
  int *b=a+n;
  int i;
  for(i=0;i<2*n;i++) scanf("%d",a+i);
  for(i=0;i<n;i++) if(a[i]<b[i]) exit(1);
  int *dp=(int *)calloc(c+1,sizeof(int));
  dp[0]=1;
  for(i=0;i<n;i++){
    for(int j=c;j>=0;j--){
      int local=0;
      for(int k=0,p=1;k<=j;k++,p=((int64)(p)*(a[i])%mod)){
 local=((local)+(((int64)(dp[j-k])*(p)%mod))<mod?(local)+(((int64)(dp[j-k])*(p)%mod)):(local)+(((int64)(dp[j-k])*(p)%mod))-mod);
      }
      dp[j]=local;
    }
  }
  printf("%d\n",dp[c]);
}
int main(void){
  run();
  return 0;
}
