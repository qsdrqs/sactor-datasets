#include<stdio.h>
#include<stdlib.h>


int enzan(int a, int b, int i) {
	if (i == 1) {
		return a - b;
	}
	else {
		return a + b;
	}
}

int main() {
	int a, b, c, d;
	int s;
	scanf("%d", &s);
	a = s/1000;
  s%=1000;
	b = s/100;
  s%=100;
	c= s/10;
  s%=10;
	d= s;

	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j <= 1; j++) {
			for (int k = 0; k <= 1; k++) {
				if (enzan(enzan(enzan(a, b, i), c, j), d, k)==7) {
					printf("%d",a);
					if (i == 1) { printf("-"); }
					else { printf("+"); }
					printf("%d",b);
					if (j == 1) { printf("-"); }
					else { printf("+"); }
					printf("%d",c);
					if (k == 1) { printf("-"); }
					else { printf("+"); }
					printf("%d=7",d);
				}
			}
		}
	}
}