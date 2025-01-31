#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
  if ( ( atoi(argv[1]) == atoi(argv[2]) ) && ( atoi(argv[2]) == atoi(argv[3]) ) && ( atoi(argv[2]) == atoi(argv[1]) ))
    printf("Yes");
  else printf("No");
}
