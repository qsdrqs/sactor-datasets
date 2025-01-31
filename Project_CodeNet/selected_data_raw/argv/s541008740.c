#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
	int a, b, c;
	if (argc != 4) return -1;
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	c = atoi(argv[3]);
	if (a <= c && c<= b) {
		printf("Yes");
	} else {
		printf("No");
	}
	return 0;
}
