#include<stdio.h>

int isprime(int n){
 int i;
 for(i=2;i*i<=n;i++){
  if(n%i==0){
   return 0;
   break;
  }
 }
 return 1;
}
int main(){
 int i,n,p1,q1;
 while(1){
  scanf("%d",&n);
  if(n==0){
   break;
  }
  if(isprime(n)==0){
   while(1){
    n--;
    if(isprime(n)==1) break;
   }
  }
  if(isprime(n)==1){
   p1=n;
   q1=n;
   for(i=n-1;i>0;i--){
    if(isprime(i)==1) q1=i;
    if(p1-q1==2){
     printf("%d %d\n",q1,p1);
     break;
    }else{
     p1=q1;
    }
   }
  }
 }
 return 0;
}
