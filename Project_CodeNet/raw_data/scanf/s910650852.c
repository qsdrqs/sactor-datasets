#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    puts((a & b & 1) ? "Yes" : "No");
    return 0;
}
