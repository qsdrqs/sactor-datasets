/* ?´???°????????°????±???????????????°?????? */
#include <stdio.h>


int main(void)
{
	int z;
	int num;
	int i, j;
	int flag;
	int count = 0;
	
	
//for(z=0; z<30; z++){	
	scanf("%d", &num);
	
	count = 0;
	for(i=2; i<=num; i++){
		flag = 0;
		for(j=2; j<num; j++){
			if(i!=j && i%j==0 ){
				flag = 1;
			//	printf("%d %d\n", i, j);
				break;
			}
			
		}
		if(flag == 0) {
		//	printf("i %d\n", i);
			count++;
		}
	}
	
			
	
	printf("%d\n", count);
//}
	return 0;
}
	