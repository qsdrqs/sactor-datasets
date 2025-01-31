#include<stdio.h>
#include<stdlib.h>
int main(int argc, char **argv) {
  int a, b;
  a = atoi(argv[1]);
  b = atoi(argv[2]);
  int c,d,e;
  c = a + b;
  d = c;
  printf("A + B = %d, ", c);
  c = a - b;
  if(c > d) {d = c;}
  printf("A + B = %d, ", c);
  c = a * b;
  if(c > d) {d = c;}
  printf("A + B = %dの中で最大の数は%dです。\n", c, d);
  return 0;
}