#include<stdio.h>
int main()
{
    int N;
    long long int mul=0;
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        if(i%3==0 || i%5==0)
            continue;
        mul=mul+i;
    }
    printf("%ld",mul);
}
