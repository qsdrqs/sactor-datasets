#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int k, p = 0, g = 0, o = 0;
	char s[100001];
	scanf("%s", s);
	for (k = 0; k < strlen(s); k++) {
		if (s[k] == 'p') p++;
		if (s[k] == 'g') g++;
	}
	k = strlen(s)/2;
	if (p < k) o = k-p;
	else o = o + (k-p);
	printf("%d\n", o);
	/*
	int n, a, b, c, d, p, a0, b0;
	scanf("%d", &n);
	if (n) {
		scanf("%d%d", &c, &d);
		n--;
	}
	while (n) {
		p = 2;
		scanf("%d%d", &a, &b);
		a0 = a, b0 = b;
		while (a0<c || b0<d) {
			a0 = a*p, b0 = b*p;
			p++;
		}
		c = a0, d = b0;
		n--;
	}
	printf("%d\n", c+d);
	*/
	return 0;
}