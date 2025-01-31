#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if (argc == 2) {
        int x = atoi(argv[1]);
        if (x >= 1 && x <= 100) {
            printf("%d\n", x*x*x);
        }
    }
    return 0;
}