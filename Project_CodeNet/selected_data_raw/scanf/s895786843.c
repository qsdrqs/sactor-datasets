#include <stdio.h>

int main(void) {
	int a,b,c,temp;
	scanf("%d",&a);
	while(scanf("%d %d %d",&a,&b,&c)!=EOF){
	//replace a<b<c
	if(a>b)
	{
		temp=a;
		a=b;
		b=temp;
	}
	if(b>c)
	{
		temp=b;
		b=c;
		c=temp;
		
	}
		if(a>b)
	{
		temp=a;
		a=b;
		b=temp;
	}
	if((a*a+b*b)==c*c)
	{
		printf("YES");
	}
	else
	{
		printf("NO");
	}
	printf("\n");
	}
	// your code goes here
	return 0;
}