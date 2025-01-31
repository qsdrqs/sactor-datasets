#include<stdio.h>
int main(void){
int n,x;
  scanf("%d%d",&n,&x);
  int l[n];
  for(int i=0;i<n;i++){
	scanf("%d",&l[i]);
  }
  int d[n+1];
  d[0]=0;
  int c=1;
  for(int i=1;i<n;i++){
	d[i]=d[i-1]+l[i-1];
    //printf("%d\n",d[i]);
    c++;
    if(d[i]>x)break;
  }
  printf("%d",c);
  return 0;
}