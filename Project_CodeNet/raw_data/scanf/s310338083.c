#include <stdio.h>
#include <string.h>
int check(int a[],int n,int m){
  int sum=0;
  while(1){
    sum+=a[n++];
    if(sum==m)
      return n;
    if(sum>m)
      return -1;
  }
}
int tanku(int a[],int n){
  n=check(a,n,5);
  if(n==-1)
    return 0;
  n=check(a,n,7);
  if(n==-1)
    return 0;
  n=check(a,n,5);
  if(n==-1)
    return 0;
  n=check(a,n,7);
  if(n==-1)
    return 0;
  n=check(a,n,7);
  if(n==-1)
    return 0;
  return 1;
}
int main(void){
  int n,i,a[40];
  char s[11];
  while(1){
    scanf("%d",&n);
    if(!n)
      break;
    memset(a,0,sizeof(a));
    for(i=0;i<n;i++){
      scanf("%s",s);
      a[i]=strlen(s);
    }
    for(i=0;i<n;i++){
      if(tanku(a,i)){
	printf("%d\n",i+1);
	break;
      }
    }
  }
  return 0;
}