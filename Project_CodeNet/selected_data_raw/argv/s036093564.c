#include <stdio.h>
#include <stdlib.h>
void main(int argc, char *argv[]){
  char* a[] = {"YES","NO"};
  printf("%s",a[atoi(argv[1])]);
}
