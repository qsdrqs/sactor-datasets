#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {
  if (argc != 4) return 1;
  int buf1, buf2, buf3;
  int a, b, c;
  a = atoi(argv[1]);
  b = atoi(argv[2]);
  c = atoi(argv[3]);
  if (0 <= a <= 100 | 0 <= b <= 100 | 0 <= c <= 100)
    {}
  else return 1;
  buf1 = a + b;
  buf2 = b + c;
  buf3 = c + a;
  if (buf1 == c | buf2 == a | buf3 == b) {
    printf("Yes\n");
  }
  else printf ("No\n");
  return 0;
}
