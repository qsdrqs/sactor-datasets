#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
	int n = atoi(argv[1]);
    int i = 0;
    double s = 0;
	for(i = 0; i < n; i++){
    	if(i%3 != 0 && i%5 != 0)
        	s += i;
    }
    printf("%lf\n", s);
    return 0;
}