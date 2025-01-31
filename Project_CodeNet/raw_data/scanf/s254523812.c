#include <stdio.h>

int main() {
	int a, v, b, w, t, k = 0;
	unsigned long long aa = 0, bb = 0;
	scanf("%d%d", &a, &v);
	scanf("%d%d", &b, &w);
	scanf("%d", &t);
    aa = a + v * t;
	bb = b + w * v;
	if (aa > bb)printf("YES");
	else printf("NO");
	return 0;
}
