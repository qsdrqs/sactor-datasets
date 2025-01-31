#include <stdio.h> 

int main(void){
	int x=0;
	int y=0;
	scanf("%d %d",&x,&y);
	while(x || y){
		if(x > y){
			printf("%d %d\n",y,x);
		}
		else{
			printf("%d %d\n",x,y);
		}
		scanf("%d %d",&x,&y);
	}
	return 0;
}