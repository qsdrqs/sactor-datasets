#include <stdio.h>

int main(void){
	int i, a, b, c, cnt=0;

	scanf("%d%d%d", &a, &b, &c);

	for(i=a; i<=b; i++){
		if(c%i == 0)
			cnt++;
	}

	printf("%d\n", cnt);

	return 0;
}