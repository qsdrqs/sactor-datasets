#include<stdio.h>
int main()
{
  int n,a[10000],d,i;
  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%d",&a[i]);
  }
  d=n-1;
  for(i=d;i>=0;i--){
    if (i>0)printf("%d ",a[i]);
    else printf("%d",a[i]);
  }
  printf("\n");
  return 0;
}
