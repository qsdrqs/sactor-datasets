#include <stdio.h>
#include <string.h>

int main(){
int x,b,a;
scanf("%d%d%d",&x,&a,&b);
if(b-a<x+1){
	
	printf("safe\n");
	
}else if(b<=a){
	
	printf("delicious\n");
	
}else if(b-a>=x+1){
	
	printf("dangerous\n");
}

	return 0;
}