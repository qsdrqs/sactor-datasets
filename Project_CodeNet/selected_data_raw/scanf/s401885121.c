/*
 ============================================================================
 Name        : atcorder_001.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int a,b;
	int total;
	int amari;

	scanf("%d", &a);
	if(a > 100 || a <= 0) {
		printf("1-100の整数を入力ください\n");
		return EXIT_FAILURE;
	}

	scanf("%d", &b);
	if(b > 100 || b <= 0) {
		printf("1-100の整数を入力ください\n");
		return EXIT_FAILURE;
	}

	total = a + b;
	amari = total%3;

	if (total >= 3 || amari == 0) {
		printf("Possible");
	}
	else {
		printf("Impossible");
	};

	return EXIT_SUCCESS;
}
