#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int N, A, B, min, max, sa;
	
	if (argc > 3) return -1;

	N = atoi(argv[0]);
	A = atoi(argv[1]);
	B = atoi(argv[2]);

	min = A + B - N;
	if (min < 0) min = 0;

	if ((A-B) > 0) {
		max = B;
	} else {
	 	max = A;
	}

	printf("%d %d\n", max, min);

	return 0;
}
