#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main(void){
  int n,m;
  int min;
  int i,j,k;
  int ans=0;
  scanf("%d %d",&n,&m);

  for(i=0;i<m;i++){
    if(m%(i+n)==0){
      printf("%d\n",m/(i+n));
      return 0;
    }
  }
  return 0;
}