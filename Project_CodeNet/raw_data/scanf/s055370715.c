#include <stdio.h>
#include <stdlib.h>

int cmp(const void * n1, const void * n2)
{
	if (*(long *)n1 > *(long *)n2)
	{
		return 1;
	}
	else if (*(long *)n1 < *(long *)n2)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

int main(void){

  long n;
  scanf("%ld", &n);
  long a[n];
  for (long i = 0; i < n; i++) {
    scanf("%ld", &a[i]);
  }

  qsort(a, sizeof(a) / sizeof(a[0]), sizeof(long), cmp);

  int flag = 1;
  for (long i = 1; i < n; i++) {
    if (a[i] == a[i-1]) {
      flag = 0;
      break;
    }
  }

  if (flag == 1) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }

  return 0;
}