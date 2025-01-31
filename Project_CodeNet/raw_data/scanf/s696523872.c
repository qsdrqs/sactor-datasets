#include <stdio.h>

int main(void){
	int n, v, t;
	scanf("%d",&n);
	int a[n],i,j;
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
		}
		
	for(t=0;t<n;t++){
	printf("%d",a[t]);
		if(t<n-1){
		printf(" ");
		}
		}
		printf("\n");
	
	for(i=1;i<n;i++){
		v=a[i];
		j=i-1;
		while(j>=0&&v<a[j]){
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=v;
		
		
		for(t=0;t<n;t++){
		printf("%d",a[t]);
			if(t<n-1){
				printf(" ");
			}
		}
		printf("\n");
	}

	return 0;
}
		

