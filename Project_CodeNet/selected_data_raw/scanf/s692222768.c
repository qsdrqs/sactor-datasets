#include <stdio.h>
int main() {
	int a=0;
	int b=0;
	int c=0;
	scanf("%d", &a);
	scanf("%d", &b);
	scanf("%d", &c);

	if (a < b&&b < c) {
		printf("%d %d %d\n",a,b,c);
	}
	if (b < a&&a < c) {
		printf("%d %d %d\n",b,a,c);
	}
	if (c < a&&a < b) {
		printf("%d %d %d\n",c,a,b);
	}
	if (a < c&&c < b) {
		printf("%d %d %d\n",a,c,b);
	}
	if (b < c&&c < a) {
		printf("%d %d %d\n",b,c,a);
	}
	if (c < b&&b < a) {
		printf("%d %d %d\n",c,b,a);
	}
	if (a == b && b == c) {
		printf("%d %d %d\n", a,b,c);
	}
	if (a == b && b < c) {
		printf("%d %d %d\n", c,b,a);
	}

	if (a == c && b < c) {
		printf("%d %d %d\n",b,c,a);
	}

	if (c == b && a < c) {
		printf("%d %d %d\n", a,b,c);
	}

	if (c == b && b < a) {
		printf("%d %d %d\n", c,b,a);
	}

	if (a == b && c > b) {
		printf("%d %d %d\n", a,b,c);
	}


	 return 0;
}
