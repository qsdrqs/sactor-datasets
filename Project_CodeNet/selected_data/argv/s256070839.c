#include <stdio.h>

int main(int argc, char *argv[])
{
    int q = 0;
    for (int i = 0; i < 3; i++)
    {
        if (argv[1][i] == 'o')
        {
            q++;
        }
    }
    int price = 700 + (q * 100);
    printf("%d\n",price);
}
