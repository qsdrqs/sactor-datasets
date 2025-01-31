#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	int n = atoi(argv[1]);
    int i;
    for(i = 100; i > 1; i/10){
		if(n/i == 7){
        	printf("Yes\n");
            return 0;
        }
        n %= i;
    }
   	if(n == 7){
    	printf("Yes\n");
    	return 0;
    }
    printf("No");
    return 0;
}