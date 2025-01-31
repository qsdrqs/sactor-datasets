#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	// your code goes here
	int x;

	if(argc >1) {
		x=atoi(argv[1]);
		printf("%d", x * x * x);
	}
	
	return 0;
}