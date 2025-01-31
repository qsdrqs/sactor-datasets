#include <stdio.h>
#include <string.h>

int main(void){

  double inputN = 0;
  double result = 0;

  scanf("%lf\n",&inputN);

  for(int i = 1;i <= inputN;i++){
    if(i % 2 == 1){
      result++;
    }
  }

  printf("%lf\n",result/inputN);

}