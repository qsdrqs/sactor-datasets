#include <stdio.h>
#include <string.h>

int main() {
    int count = 0;
    char str1[200000];
    char str2[200000];

    scanf("%s", str1);
    scanf("%s", str2);
        
    for (int i = 0; i < strlen(str1); i++) {
        if (str1[i] != str2[i]) {
            count += 1;
        }
    }

    printf("%d\n", count);    
    return 0;
}