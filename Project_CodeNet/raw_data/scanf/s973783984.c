#include <stdio.h>
int main(void)
{
  int i, j, a;
  int x[i], V[i], C[i];
  scanf("%d", &i);
  for(j=0; j<i; j++){
    scanf("%d", &V[j]);
  }
  for(j=0; j<i; j++){
    scanf("%d", &C[j]);
  }
  for(j=0; j<i; j++){
    x[j]=V[j]-C[j];
    if(x[j]>0){
      a=a+x[j];
    }
  }
  printf("%d\n", a);
  return 0;
}