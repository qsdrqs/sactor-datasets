#include<stdio.h>

#define N 5

int main(void)
{
    int arg[N];
    int i, count = 0;
    
    for(i=0; i<5; i++) {
        scanf("%d", &arg[i]);
        if(arg[i] == 0) {
            count = i+1;
        }
    }

    printf("%d\n", count);


    return 0;
}