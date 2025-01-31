#include<stdio.h>
int main(void){
	int idx[100100]={0};
	long sum=0;
	int a,n,q,b,c;
	int i;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d",&a);
		idx[a]++;
		sum+=a;
	}
	scanf("%d",&q);
	for(i=0;i<q;i++){
		scanf("%d%d",&b,&c);
		sum+=(c-b)*idx[b];
		idx[c]+=idx[b];
		idx[b]=0;
		printf("%ld\n",sum);
	}
	return 0;
}
