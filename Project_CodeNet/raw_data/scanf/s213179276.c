#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char n,l,max=0,i;
	int sum=0;
	scanf("%hhd",&n);
	for (i=0;i<n;i++) {
		scanf("%hhd",&l);
		if (max < l) max = l;
		sum += l;
	}
	
	if (max < sum-max) printf("Yes\n");
	else printf("No\n");

	return 0;
}
