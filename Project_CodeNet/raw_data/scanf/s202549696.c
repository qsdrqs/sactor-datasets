#include <stdio.h>
int main(void)
{
  int N;
  scanf("%d", &N);
  if(N % 10 == 7 || N % 100 / 10 == 7 || N % 1000 / 100 == 7) 
    printf("Yes\n");
  else 
    printf("No\n");
}