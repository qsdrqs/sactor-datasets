#include <stdio.h>

int main(void) {
	int n, i = 1;
	
	scanf("%d", &n);
	while(1){
		if(i % 3 == 0){
			printf(" %d", i);
			i ++;	
		} 
		else if(i % 10 == 3){
			printf(" %d", i);
			i++;	
		}
		else if(i <= n) i++; 
		else break;
	}
	printf("\n");
	return 0;
}