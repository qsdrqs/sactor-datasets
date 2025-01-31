#include<stdio.h>

int main(){
  long long n,k,point,loop,time1,time2;
  scanf("%lld%lld",&n,&k);
  long long a[n+1],b[n+1];
  for(long long i=1;i<=n;i++){
    scanf("%d",&a[i]);
    b[i]=0;
  }
  point=1;
  b[1]=1;
  for(long long i=1;i<=n;i++){
    point=a[point];
    if(b[point]==2){
      loop=point;
      time2=i;
      break;
    }
  }
  point=1;
  for(long long i=1;i<=n;i++){
    point=a[point];
    if(point==loop){
      time1=i;
    }
  }
  k=(k-time1)%(time2-time1);
  point=loop;
  for(long long i=1;i<=k;i++){
    point=a[point];
  }
  printf("%lld",point);
  return 0;
}
