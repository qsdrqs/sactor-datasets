#include<stdio.h>
#include<stdbool.h>
int main()
{
    char s[10],t[11];
    bool ok=true;
    scanf("%s",s);
    scanf("%s",t);
    for(int i=0; s[i]!='\0'; i++)
    {
        if(s[i]!=t[i]) { printf("No"); ok=false; break; }
    }
    if(ok) printf("Yes");
    return 0;
}
