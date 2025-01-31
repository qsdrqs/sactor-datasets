#include <stdio.h>

int main(void)
{

  int N;

  scanf ("%d", &N);

  int x=N%10;
  int y=(N-x)/10;

  if (x==9) {
    printf ("YES"); }

  else if (y==9) {
    printf ("YES"); }

  else {
    printf ("NO"); }

  return (0);
}