#include <stdio.h>
#define MARK 4
#define RANK 13
#define CHECK 1	
int main(void)
{
	int n,rank,a,i,k;
	char mark;
	int card[4]={0,0,0,0};
	char mk[4]={'S','H','C','D'};
	scanf("%d", &n);
	for(i=0; i<n; i++){
		scanf(" %c %d", &mark, &rank);
		if(mark == 'S'){
			a=1;
			a <<= rank;
			card[0] += a;
		}else if(mark == 'H'){
			a=1;
			a <<= rank;
			card[1] += a;
		}else if(mark == 'C'){
			a=1;
			a <<= rank;
			card[2] += a;
		}else if(mark == 'D'){
			a=1; 
			a <<= rank;
			card[3] += a;
		}
	}
	for(i=0; i<MARK; i++){
		for(k=1; k<=RANK; k++){
			card[i] >>= 1;
			if((card[i] & CHECK) == 0){
				printf("%c %d\n", mk[i], k);
			}
		}
	}
	return 0;
}