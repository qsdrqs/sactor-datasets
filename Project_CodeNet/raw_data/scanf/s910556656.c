#include<stdio.h>

int main()
{
    int n;
    int a, b;

    scanf("%d", &n);
    a = n / 100;
    b = n % 100;

    if ((1 <= a) && (12 >= a)) {
        if ((1 <= b) && (12 >= b)) {
            printf("AMBIGUOUS\n");
        }
        printf("MMYY\n");
    }
    else if ((1 <= b) && (12 >= b)) {
        printf("YYMM\n");
    }
    else {
        printf("NA\n");
    }
    return 0;
}