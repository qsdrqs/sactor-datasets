#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {
  if (argc != 4) return 1;
  int buf1, buf2, buf3;
  buf1 = atoi(argv[1]) + atoi(argv[2]);
  buf2 = atoi(argv[2]) + atoi(argv[3]);
  buf3 = atoi(argv[1]) + atoi(argv[3]);
  if (buf1 == atoi(argv[3]) | buf2 == atoi(argv[1]) | buf3 == atoi(argv[2])) {
    printf("Yes\n");
  }
  else printf ("No\n");
  return 0;
}
