#include <stdio.h>

int main(int argc, char const *argv[]) {
  char a = *argv[0];
  char b = *argv[1];
  int max = 0;
  for (size_t i = 0; i < 2; i++) {
    if (a >= b) {
      max += a;
      a--;
    } else {
      max += b;
      b--;
    }
  }
  return max;
}
