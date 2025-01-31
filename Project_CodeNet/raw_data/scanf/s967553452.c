#include<stdio.h>
int main(){
  
  int n,i,j,k,key,a[100];
  scanf("%d",&n);
  for(i=1;i<=n;i++){
    scanf("%d",&a[i]);
  } 
  printf("\n");

  for(k=1;k<=n;k++){
    printf("%d ",a[k]);
  }
  printf("\n");
  for(i=2;i<=n;i++){
    key=a[i];
    j=i-1;
    while(j>=0 && a[j]>key){
      a[j+1]=a[j];
      j=j-1;
    }
    a[j+1]=key;
    for(k=1;k<=n;k++){
      if(k==n)printf("%d",a[k]);
      else printf("%d ",a[k]);
    }
    printf("\n");
  }
  return 0;
}