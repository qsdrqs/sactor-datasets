#include <stdio.h>
#include <math.h>
int main(){
  long int i,n,f=1,c=1e9+7;
  scanf("%d",&n);
  for (;i++<n;) f=f*i%c;
  printf("%d",f);
  return 0;
}