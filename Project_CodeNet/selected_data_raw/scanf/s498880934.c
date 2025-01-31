#include <stdio.h>
#include <string.h>

int main(void)
{
	int n, m, len, count;
	int i;
	static char str[1000001], ioi[2000001];
	
	while (1){
		strcpy(ioi, "IOI");
		scanf("%d", &n);
		
		if (!n) break;
		
		for (i = 0; i < n - 1; i++){
			strcat(ioi, "OI");
		}
		scanf("%d", &m);
		scanf("%s", str);
		getchar();
		len = strlen(ioi);
		count = 0;
		for (i = 0; i < m - len; i++){
			if (strncmp(&str[i], ioi, len) == 0){
				count++;
				i += 1;
			}
		}
		printf("%d\n", count);
	}
	return (0);
}