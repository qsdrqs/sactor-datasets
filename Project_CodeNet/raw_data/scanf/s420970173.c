#include <stdio.h>
int main(){
	int i,j,n,tmp,min,count=0;
	int a[100];
	scanf("%d",&n);
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	
	for(i=0;i<n;i++){
		min=i;
		for(j=i;j<n;j++){
			if(a[min]>a[j]) min=j;
		}
		if(i!=min){
			tmp=a[min];
			a[min]=a[i];
			a[i]=tmp;
			count++;
		}
	}
	for(i=0;i<n-1;i++)printf("%d ",a[i]);
	printf("%d\n",a[i]);
	printf("%d\n",count);	
return 0;
}