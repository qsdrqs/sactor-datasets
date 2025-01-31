#include <stdio.h>

int main(int argc, char *argv[]){
	int a = 0;
	int i;
	for(i=0;i<argc;i++){
		if(argv[1][i] == 1)a++;
	}
	printf("%d",a);
	
	return 0;
}