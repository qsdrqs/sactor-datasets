#include <stdio.h>
int main()
{
    int D, T, S;
    double A;

    scanf("%d %d %d", &D, &T, &S);
    A = D / S;

    if (A > T)
    {
        printf("NO");
    }
    else
    {
        printf("Yes");
    }
    return 0;
}