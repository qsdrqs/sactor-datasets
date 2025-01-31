#include <stdio.h>
#define NMAX 10001
int main(void)
{
    int H, N, A[NMAX], sum = 0;
    scanf("%d%d", &H, &N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
        sum += A[i];
    }
    if (sum >= H)
        printf("Yes");
    else
        printf("No");

    return 0;
}