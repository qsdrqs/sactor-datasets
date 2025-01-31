#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	int a = 0;
	int i;
	for(i=0;i < strlen(argv[1]);i++){
		if(argv[1][i] == 1)a++;
	}
	printf("%d",a);
	
	return 0;
}