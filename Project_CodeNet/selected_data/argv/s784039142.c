#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countd(int l, int r, int d) {
    int count = 0;
    for (int i = l; i <= r; i++) {
        if (i % d == 0) {
            count++;
        }
    }
    return count;
}
int main(int argc, char **argv) {
    int l, r, d, ans;
    l = atoi(argv[1]);
    r = atoi(argv[2]);
    d = atoi(argv[3]);
    ans = countd(l, r, d);
    printf("%d\n", ans);
    return 0;
}
