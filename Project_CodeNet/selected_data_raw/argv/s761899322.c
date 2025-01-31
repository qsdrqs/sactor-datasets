#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int is_num(const char *str, size_t length);

int main(int argc, char *argv[])
{
	int status = 1;
	int max_num;
	int x;
	int a;
	int b;
	int i;
	int tmp;

	max_num = (int)pow(10, 9);

	if (argc != 4) {
		goto end;
	}

	for (i = 1; i < argc; i++) {
		if (is_num(argv[i], strlen(argv[i])) == 0) {
			goto end;
		}
		tmp = atoi(argv[i]);
		if (tmp < 1 || tmp > max_num) {
			goto end;
		}
	}

	x = atoi(argv[1]);
	a = atoi(argv[2]);
	b = atoi(argv[3]);

	if (b <= a) {
		printf("delicious\n");
	} else if (b <= a + x) {
		printf("safe\n");
	} else {
		printf("dangerous\n");
	}

	status = 0;

end:
	if (status != 0) {
		fprintf(stderr, "Parameter error.\n");
	}

	return status;
}

static int is_num(const char *str, size_t length)
{
	int i;

	for (i = 0; i < length; i++) {
		if (str[i] < '0' || str[i] > '9') {
			break;
		}
	}

	return (i >= length);
}
