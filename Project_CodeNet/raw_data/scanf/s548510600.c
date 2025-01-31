#include<stdio.h>
 
int main()
{
	int n,b = 0,w = 0,i;
	scanf("%d",&n);
  
  	char c[n];
	scanf("%s",c);
	
	for(i = 0;i < n;i++){
		if(c[i] == '.') w++;
	}
	
	int min = w;
  
	for(i = 0;i < n;i++){
		if(c[i] == '#') b++;
		else w--;
		if(b + w < min) min = b + w;
	}
	printf("%d",min);
	return 0;
}