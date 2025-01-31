#include <stdio.h>
int main(void)
{
  char str[256];
  scanf("%s", str);
  int j = 0;
  for(int i = 0;str[i] != '\0';i++){
    if(i % 2 == 0){if(str[i] == 'R'){j++;}}
    if(i % 2 == 1){if(str[i] == 'L'){j++;}}
   }
  if(j == 0){printf("Yes");}
  if(j != 0){printf("No");}
  return 0;
}
