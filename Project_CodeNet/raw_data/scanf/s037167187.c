#include<stdio.h>
#include<stdlib.h>
#define d_flag 0
int C(const void *a,const void *b){
  return *(int*)b-*(int*)a;
}

int main(){
  int n,K,count=0;
  scanf("%d%d",&n,&K);
  int i,a[n];
  for(i=0;i<n;i++){
    scanf("%d",&a[i]);
    if(a[i]>=K){
      i--;
      n--;
    }
  }
  qsort(a,n,sizeof(int),C);
  if(d_flag) {
    for(i=0;i<n;i++)
      printf(" %d",a[i]);
    printf("\n");
  }
  int dp[K+1],j,k,flag;
  for(i=0;i<n;i++){
    if(a[i]>=K)continue;
    flag=1;
    for(j=0;j<=K;j++){
      dp[j]=0;
    }
    dp[0]=1;
    for(k=0;k<n;k++){
      if(k==i)continue;
      for(j=K-a[k];j>=0;j--){
	if(dp[j]==1) {
	  dp[j+a[k]]=1;
	  if(j+a[k]>=K-a[i]){
	    flag=0;
	    break;
	  }
	}
	if(flag==0)break;
      }
      if(flag==0)break;
    }
    if(flag==0)continue;
    /*
    for(j=K-a[i];j<K;j++)
      if(dp[j]==1) flag=0;
    */
    count++;
    if(d_flag){
      printf("without a[%d]=%d:\n",i,a[i]);
      int kkk;
      for(kkk=0;kkk<=K;kkk++)printf(" %d",dp[kkk]);
      printf(" ,flag:%d\n",flag);
    }
  }
  printf("%d",count);
}
