#include <stdio.h>

int main () {

    int n, x, i, j, k, y;

    for (; ; ) {

        y = 0;

        scanf("%d", &n); scanf("%d", &x);

        if (n == 0 && x == 0) {
            break;
        }

        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++){
                for (k = 1; k <= n; k++) {
                    if (i + j + k == x && i < j && j < k) {
                        y += 1;
                    }
                }
            }
        }

        printf("%d\n", y);

    }

    return 0;

}

