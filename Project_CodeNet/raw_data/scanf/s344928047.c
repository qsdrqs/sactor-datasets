#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x,a;
    scanf("%d %d",&x,&a);
    if(x>=0&&a<=9)
    {
    if(x<a)
        printf("0");
    else if(x>a)
        printf("10");


    }
    return 0;
}
