#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
    int k = atoi(argv[1]);
    int x = atoi(argv[2]);
    int sum = 500*k;
    if(sum < x)
    {
        printf("No\n");
    }
    else{
        printf("Yes\n");
    }
    return 0;
}
