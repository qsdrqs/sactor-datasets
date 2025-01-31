#include <stdio.h>
#include <math.h>
#include <string.h>
char a[5][5];
int main()
{
    while(1)
    {
        for(int i=0; i<2; i++)
        {
            scanf("%s",&a[i]);
        }
        if(a[0][0]==a[1][2]&&a[0][1]==a[1][1]&&a[0][2]==a[1][0])
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    return 0;
}