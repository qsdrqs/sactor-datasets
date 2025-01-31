#include<stdio.h>
int main(void){
	int m[101][101]={0},i,j,c,r;
	scanf("%d %d",&r,&c);
	for(i=0;i<c;i++){
		for(j=0;j<r;j++){
			scanf("%d",&m[i][j]);
		}
	}
	for(i=0;i<c;i++){
		for(j=0;j<r;j++){
			m[i][c]+=m[i][j];
			m[r][j]+=m[i][j];
			m[r][c]+=m[i][j];
		}
	}
	for(i=0;i<=c;i++){
		for(j=0;j<=r;j++){
			printf("%d",m[i][j]);
			if(j==r) printf("\n");
		}
	}
	return 0;
}