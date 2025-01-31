#include <stdio.h>
 
int main(int argc, char *argv[])
{
  int i = 0;
  int j;
  
  (void)argc;
  while (argv[1][i])
  {
    j = i;
    while (argv[1][j])
    {
      if (argv[1][j] == argv[1][i])
      {
        printf("no");
        return (0);
      }
      j++;
    }
    i++;
  }
  printf("yes");
  return (0);
}