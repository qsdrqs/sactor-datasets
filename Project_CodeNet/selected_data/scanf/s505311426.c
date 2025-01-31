
// AOJ Volume 0 Problem 0008

#include <stdio.h>

char flg_prime[1000000 / 2];
int main(void)
{
    int i;
    int j;
    int n;
    int c;
    for (i = 3; i <= 999999; i++){
        if ((flg_prime[((i) / 2) - 1]) == 0){
            j = i * 2;
            while (j <= 999999){
                if (j % 2 != 0){
                    (flg_prime[((j) / 2) - 1] = 1);
                }
                j += i;
            }
        }
    }
    while (scanf("%d", &n) != (-1)){
        if (n < 2){
            printf("0\n");
            continue;
        }
        if (n == 2){
            printf("1\n");
            continue;
        }
        c = 1;
        for (i = 3; i <= n; i += 2){
            if ((flg_prime[((i) / 2) - 1]) == 0){
                c++;
            }
        }
        printf("%d\n", c);
    }
    return (0);
}
