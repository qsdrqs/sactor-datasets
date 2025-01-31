#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
 int A = atoi(argv[1]);
 int B = atoi(argv[2]);
 int X = atoi(argv[3]);
 if (A <= X && A + B >= X) {
  printf("YES");
 }
 else {
  printf("NO");
 }
 return 0;
}
