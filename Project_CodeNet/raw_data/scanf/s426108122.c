#include <stdio.h>

int main(void)
{

    int a, b;
    int d, r;
    float f;

    scanf("%d %d", &a, &b);


    d = a / b;
    r = a % b;
    f = a / b;

    printf("%d %d %6.5f\n", d, r, f);
    return 0;
}