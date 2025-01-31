#include <stdio.h>
#include <string.h>
int main() {
	char str[300],str1[101], str2[101];
	scanf("%s", str1);
	scanf("%s", str2);
	strcpy(str, str2);
	strcat(str, str2);
	if (strstr(str, str2)==NULL)
		printf("No\n");
	else
		printf("Yes\n");
}
