#include<stdio.h>
#include<stdlib.h>

int compare_double(const void *a, const void *b)
{
    return *(double*)a - *(double*)b;
}
int main()
{
    double n;
    scanf("%lf", &n);
    double a[200005];
    long i;
    for (i = 0; i < n; i++)
        scanf("%lf", &a[i]);
    double b[200005];
    b[0] = a[0];
    for (i = 1; i < n; i++)
        b[i] = b[i - 1] + a[i];
    double ans = 0;
    qsort(b, n, sizeof(double), compare_double);
    double y;
    if (b[0] == 0)
        ans++;
    y = 0;
    i = 1;
    while (i < n)
    {
        if (b[i] == 0)
            ans++;
        if (b[i] == b[i - 1])
            y++;
        else
            y = 0;
        ans += y;
        i++;
    }
    printf("%.0lf\n", ans);
    return 0;
}
