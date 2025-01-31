#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
	int sr;
	int i;
	int N;

	N = atoi(argv[1]);

	printf("%d\n", N);

	srand(time(NULL));
	printf("%d", rand()%2);
	for (i=1; i<N; i++) {
		printf(" %d", rand()%2);
	}
	printf("\n");
}

