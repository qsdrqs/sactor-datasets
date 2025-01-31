#include<stdio.h>
#include<stdlib.h>

int main()
{
	int N,j_num=0,two_num=0,four_num=0;
	scanf("%d",&N);
	
	long long *a;
	a=(long long*)malloc(N*sizeof(long long));
	
	for(int i=0;i<N;i++)
	{
		scanf("&lld",&a[i]);
		
		if(a[i] & 1)
			j_num++;
		else if(!(a[i]%4))
			four_num++;
		else 
			two_num++;	
	}
	
	if(two_num==0 && j_num>(four_num+1))
		printf("No\n");
	else if(two_num && j_num>four_num)
		printf("No\n");
	else
		printf("Yes\n");
	
	return 0;
}