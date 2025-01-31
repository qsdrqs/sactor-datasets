#include <stdio.h>

int main(void)
{
    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d %d\n", x * y, 2 * (x + y));
    return 0;
}