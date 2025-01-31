#include <stdio.h>

int main()
{
  int N, num;

  scanf("%d", &N);

  num = N % 10;

  if(num == 3){
    printf("bon\n");
  }
  else if(num == 0 || num == 1 || num == 6 || num == 8){
    printf("pon\n");
  }
  else{
    printf("hon\n");
  }

    return 0;
  }
