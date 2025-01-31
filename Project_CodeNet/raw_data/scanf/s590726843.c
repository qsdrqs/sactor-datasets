#include <stdio.h>
int main(void)
{
  int daikin;
  int oturi;
  int maisu = 0;
  

  scanf("%d", &daikin);
  oturi = 1000 - daikin;

  if(oturi /  500 >= 1){
    maisu +=  oturi / 500;
    oturi = oturi % 500;
  }

  if(oturi / 100 >= 1){
    maisu += oturi / 100;
    oturi = oturi % 100;
  }

  if(oturi / 50 >= 1){
    maisu += oturi / 50;
    oturi = oturi % 50;
  }

  if(oturi / 10 >= 1){
    maisu += oturi/ 10;
    oturi = oturi % 10;
  }
  
  if(oturi / 5 >= 1){
    maisu += oturi / 5;
    oturi = oturi % 5;
  }

  if(oturi / 1 >= 1){
    maisu += oturi / 1;
  }
  printf("%d\n", maisu);

  return 0;
}