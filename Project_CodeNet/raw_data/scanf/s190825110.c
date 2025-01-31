#include <stdio.h>

int main()
{
	int N, Y, x, y,z;
	scanf("%d %d", &N, &Y);
		for (y = 0; y <= (Y / 5000); y++) {
			for (x = 0; x <= (Y / 10000); x++) {
				z = N - x - y;
				if ((x + y + z) == N && Y - (10000 * x + 5000 * y + 1000 * z) == 0) {
					printf("%d\t%d\t%d\t\n", x, y, z);
					return 0;
				}
			}
		}
	printf("-1 -1 -1\n");
	return 0;
}