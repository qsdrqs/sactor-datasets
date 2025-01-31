#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int i,j,a,b,c,ans=0;

int main(){
	for(j=0;j<3;j++){
	scanf("%d %d",&a,&b);
	c=a+b;
	while(c!=0)c=c/10,ans++;
	printf("%d",ans);
	}
	return 0;
}