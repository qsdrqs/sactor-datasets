#include <stdio.h>

int main()
{
    int a, b, c;
    int max;            // a, b, cのうち最大のもの
    int x;              // a, b, cの最終的な値
    
    scanf("%d %d %d", &a, &b, &c);

    // maxを求める
    max = a;
    if (max < b)
    {
	max = b;
    }
    if (max < c)
    {
	max = c;
    }

    // xを求める
    if (((3 * max) % 2) == ((a + b + c) % 2))
    {
	x = max;
    }
    else
    {
	x = max + 1;
    }

    printf("%d\n", ((3 * x) - (a + b + c)) / 2);

    return 0;
}
