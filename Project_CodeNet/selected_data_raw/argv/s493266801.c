#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[]){
	int a,b,count=0;
	int month = atoi(argv[1]);
	int day =  atoi(argv[2]);
	for(a=1;a <= month;a++){
		for(b=1;b<= day;b++){
			if(a == b) count++;
		}
	}
	printf("%d\n",count);
return 0;
}