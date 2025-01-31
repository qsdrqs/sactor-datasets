#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
 int a, b;
 a = atoi(argv[1]);
 b = atoi(argv[2]);
 if (a + b >= 10) {
  printf("error\n");
  exit(2);
 }
 else {
  printf("%d\n", a + b);
 }
 return(0);
}
