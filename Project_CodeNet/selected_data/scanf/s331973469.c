#include <stdio.h>
#include <string.h>

int func(char* s, int n, int isleft)
{
    int i, left=-1, right=-1;
    int res=0;
    if (isleft) left=s[0]; else right=s[0];
    isleft=!isleft;
    for(i=1;i<n;++i) {
        if (isleft) {
            if ((((s[i])%3==0?3:(s[i])%3)>((right)%3==0?3:(right)%3))) { ++res; right=s[i]; }
            else { left=s[i]; isleft=!isleft; }
        }
        else {
            if ((((left)%3==0?3:(left)%3)>((s[i])%3==0?3:(s[i])%3))) { ++res; left=s[i]; }
            else { right=s[i]; isleft=!isleft; }
        }
    }
    return res;
}
char s[100001];
int main(void)
{
    while (scanf("%s", s), *s!='#') {
        int n=strlen(s), i;
        int L, R;
        for(i=0;i<n;++i) s[i]-='0';
        L=func(s, n, 1);
        R=func(s, n, 0);
        printf("%d\n", L<R?L:R);
    }
    return 0;
}
