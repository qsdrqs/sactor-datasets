#include<stdio.h>
int main(void){
  int N,x;
  int ans=0;
  scanf("%d %d",&N,&x);
  int a[N-1];
  for(int i=0;i<=N-1;i++)
    scanf("%d",&a[i]);
   
  for(int i=0;i<=N-1;i++){
    if(x>=a[i]){
     ans+=1;
     x=x-a[i];
     }
   }
  if(x!=0&&ans!=0)  ans=ans-1;
  printf("%d",ans);  
  return 0;
}