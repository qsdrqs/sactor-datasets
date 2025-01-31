#include <stdlib.h>

int		main(int argc, char **argv)
{
  int i;
	int n;
  int x;
  int t;

  if (!(argc ==4))
    return (0);
  n = atoi(argv[1]);
  x = atoi(argv[2]);
  t = atoi(argv[3]);
  i = n / x + 1;
  return ( i * t);
}