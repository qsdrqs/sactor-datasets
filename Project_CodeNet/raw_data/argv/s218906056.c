#include <stdio.h>
 
int main(int argc, char *argv[])
{
  int n = *argv[1];
  int m = *argv[2];
  int count = (n * (n - 1) / 2);
  printf("%i", count);
  return count;
}
