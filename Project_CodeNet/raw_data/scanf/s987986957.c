#include <stdio.h>

void main(void)
{
        int k, s;
        int x, y, z;
        int p = 0;

        (void)scanf("%d %d", &k, &s);
        for (x = 0; x <= k; x++) {
                for (y = 0; y <= k; y++) {
                        for (z = 0; z <= k; z++) {
                                if (x + y + z == s)
                                        p++;
                        }
                }
        }
        printf("%d", p);
}
