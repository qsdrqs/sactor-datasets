#include <stdio.h>
#include <string.h>
int main(void) {
  char S[100];
  scanf("%s", S);
  int l = strlen(S);
  for (int i = 0; i < l; i++) {
    S[i] = 'x';
  }
  printf("%s\n", S);
  return 0;
}