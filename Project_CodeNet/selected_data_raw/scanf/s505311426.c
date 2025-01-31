
// AOJ Volume 0 Problem 0008

#include <stdio.h>

#define GET_FLG(n)  (flg_prime[((n) / 2) - 1])
#define SET_FLG(n)  (flg_prime[((n) / 2) - 1] = 1)


char flg_prime[1000000 / 2];

int main(void)
{
    int i;
    int j;
    int n;
    int c;
    
    for (i = 3; i <= 999999; i++){
        if (GET_FLG(i) == 0){
            j = i * 2;
            while (j <= 999999){
                if (j % 2 != 0){
                    SET_FLG(j);
                }
                j += i;
            }
        }
    }

    while (scanf("%d", &n) != EOF){
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
            if (GET_FLG(i) == 0){
                c++;
            }
        }
        printf("%d\n", c);
    }
    
    return (0);
}


#if 0
int isprime(int n)
{
    int i;

    if (n == 2){
        return (1);
    }

    if (n % 2 == 0){
        return (0);
    }

    for (i = 3; i * i <= n; i += 2){
        if (n % i == 0){
            return (0);
        }
    }
    return (1);
}

int main(void)
{
    int n;
    int i;
    int c;
    
//    while (scanf("%d", &n) != EOF){
    scanf("%d", &n);
        if (n == 2){
            printf("1\n");
            return (0);
        }

        c = 1;
        for (i = 3; i <= n; i+=2){

//            printf("%d - %d\n", i, isprime(i));
            c += isprime(i);
        }

        printf("%d\n", c);
// }

    return (0);
}
#endif