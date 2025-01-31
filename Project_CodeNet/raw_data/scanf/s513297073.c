/* ITP1_3_C:Swapping Two Numbers  */
/* 20181118 AOJ */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void){
	int x, y;

	while(1){
		scanf("%d %d", &x, &y);
		if( !x && !y) break;
		if(x >= y){
			printf("%d %d\n", y, x);
		}else{
			printf("%d %d\n", x, y);
		}
	}

	return 0;
}


