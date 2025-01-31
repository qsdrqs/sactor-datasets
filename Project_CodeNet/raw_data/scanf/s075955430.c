#include <stdio.h>

int main(int argc, char *argv[])
{
    char str[256];
    scanf("%s",str);

    if((str[0]==str[1])&&(str[1]==str[2]))
    {
       printf("Yes");
    }
    return 0;
}

