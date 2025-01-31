#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    int a, b, i, c1=0, r=-2, c2=0, w=-1, sum=0;
    scanf("%d%d", &a, &b);
    for(i=0; i<b; i++)
    {
        char s[3];
        int x;
        scanf("%d", &x);
        scanf("%s", &s);
        if(s[0]=='A' && s[1]=='C' && x!=r)
        {
            r = x;
            c1++;
        }
        else if(s[0]=='W' && s[1]=='A' && x!=w)
        {
            w = x;
            c2++;
        }
    }
    printf("%d %d\n", c1, c2);
    return 0;
}
