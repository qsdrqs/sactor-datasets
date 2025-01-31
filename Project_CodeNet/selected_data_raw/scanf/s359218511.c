#include<stdio.h>
#include<stdlib.h>

typedef long long int int64;

const int mod=1000000007;

#define ADD(a,b) ((a)+(b)<mod?(a)+(b):(a)+(b)-mod)
#define MUL(a,b) ((int64)(a)*(b)%mod)

int modPow(int r,int n){
  int t=1;
  int s=r;
  while(n>0){
    if(n&1) t=MUL(t,s);
    s=MUL(s,s);
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
      for(int k=0,p=1;k<=j;k++,p=MUL(p,a[i])){
	local=ADD(local,MUL(dp[j-k],p));
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
