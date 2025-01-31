#include <stdio.h>
#include <string.h>

long A_[300300];
long bubbleSort(long* A, long N)
{
 long flag=1;
 long i,tmp;
 while(flag){
  flag = 0;
  for(i=N-1;i>0;i--){
   if(A[i]<A[i-1]){
    tmp = A[i];
    A[i]=A[i-1];
    A[i-1]=tmp;
    flag=1;
//				cnt++;
   }
  }
 }
 return 0;
}
int main(){
 long N,max=-100;
 long i,j,dat;
 char s[110];
 scanf("%ld",&N);
 for(i=0;i<N;i++){
  scanf("%ld",&A_[i]);
  //A[dat]=1;
  //if(max<dat)max=dat;
 }
 //bubbleSort(A_, N);
 int cnt=0;
 long ans=0,tmp=-1,tmp2=0;
 for(i=0;i<N-1;i++){
   if(tmp!=A_[i]){
    tmp2=0;
      // printf("in:%ld\n",A_[i]);
    for(j=i+1;j<N;j++){
//					if(A[j]==1){
      tmp2 +=A_[i]^A_[j];
      //printf("%ld:%ld %ld %ld\n",i,ans,A[i],A[j]);
//					}
    }
    tmp = A_[i];
    ans +=tmp2;
    if(ans>1000000007)ans %= 1000000007;
   }
   else{
    ans +=tmp2;
    if(ans>1000000007)ans %= 1000000007;
   }
  //}
 }
  printf("%ld\n",ans);
 return 0;
 }
