#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "[USAGE] %s |AB| |BC| |CA|\n", argv[0]);
  }
  int ab = atoi(argv[1]);
  int bc = atoi(argv[2]);
  // int ca = atoi(argv[3]);
  
  fprintf(stdin, "%d\n", ab * bc / 2);
  
  return 0;
}
