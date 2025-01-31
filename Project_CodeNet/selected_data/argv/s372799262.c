#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
 int N=0, A=0, B=0, min=0, max=0, sa=0;
 N = atoi(argv[0]);
 A = atoi(argv[1]);
 B = atoi(argv[2]);
 min = A + B - N;
 if (min < 0) min = 0;
 if ((A-B) > 0) {
  max = B;
 } else {
   max = A;
 }
 printf("%d %d\n", max, min);
 return 0;
}
