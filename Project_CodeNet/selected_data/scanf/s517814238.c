#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N, M;
    scanf("%d%d", &N, &M);
    int l[M], r[M];
    int i, min = 100000, max = 0;
    for (i = 0; i < M; i++)
    {
        scanf("%d%d", &l[i], &r[i]);
        if (l[i] > max)
        {
            max = l[i];
        }
        if (r[i] < min)
        {
            min = r[i];
        }
    }
    if (min - max >= 0)
    {
        printf("%d\n", min - max + 1);
    }
    else
    {
        printf("0\n");
    }
    return 0;
}
