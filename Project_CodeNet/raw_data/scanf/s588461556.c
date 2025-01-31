#include<stdio.h>
void swap(int *x, int *y)
{
	int t;
	t = *x, *x = *y, *y = t;
}
int main()
{
	int w, x[30], n, h1, h2, i;
	scanf("%d%d", &w, &n);
	for (i = 0; i < w; i ++)
		x[i] = 1+i;
	for (i = 0; i < n; i ++) {
		scanf("%d,%d", &h1, &h2);
		swap (&x[h1-1], &x[h2-1]);
	}
	for (i = 0; i < w; i ++)
		printf("%d\n", x[i]);
	return 0;
}