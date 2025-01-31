#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int x, cubic;
  x = atoi(argv[1]);
  cubic = x*x*x;
  printf("%d\n", cubic);
  return 0;
}
