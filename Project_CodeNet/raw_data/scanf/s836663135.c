#include <stdio.h>

int main (void) {
    int cnt = 15, s = 0;
    char i, *mes = "YES";
    while (1)
    {
        scanf("%c", &i);
        if (i=='\n') break;
        if (i=='o') s++;
        cnt--;
    }
    if (cnt+s<8) mes = "NO";
    printf("%s\n", mes);
}