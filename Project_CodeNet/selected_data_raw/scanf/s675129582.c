#include <stdio.h>
int main(void){
	while(1){
		int h,w;
		scanf("%d %d\n",&h,&w);
		if(h==0 && w==0){
			break;
		}else{
			int x,y;
			for(x=0;x<h;x++){
				for(y=0;y<w;y++){
					if(x==0 || x==h-1){
						printf("#");
					}else if(y==0 || y==w-1){
						printf("#");
					}else{
						printf(".");
					}
					if(y==w-1){
						printf("\n");
					}
				}
			}
		printf("\n");
		}
	}
}