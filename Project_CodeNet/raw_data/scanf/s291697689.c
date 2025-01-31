#include <stdio.h>

int main(void)
{
    unsigned int inputN, total = 0;
    int inputK, tmp;

    scanf("%u%d", &inputN, &inputK);
    for (int index = 0; index < inputN; index++)
    {
        scanf("%d", &tmp);
        if (tmp >= inputK)
        {
            total++;
        }
    }

    printf("%u", total);

    return 0;
}