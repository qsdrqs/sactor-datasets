#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[]){
	int count=0;
	int month = atoi(argv[1]);
	int day =  atoi(argv[2]);
	for(int a=1;a <= month;a++){
		for(int b=1;b<= day;b++){
		if(a == b){ count++;
		printf("a=%d\tb=%d\n",a,b);
		break;}
		}
	}
	printf("%d\n",count);
return 0;
}