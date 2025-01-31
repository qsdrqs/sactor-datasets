#include <stdio.h>
int main(){
	int n;
	int i,a,b,asum,bsum;
	scanf("%d",&n);
	while(n!=0){
		asum=0;
		bsum=0;
		for(i=0;i<n;i++){
			scanf("%d %d",&a,&b);
			if(a>b){
				asum+=a+b;
			}
			else if(a==b){
				asum+=a;
				bsum+=b;
			}
			else{
				bsum+=a+b;
			}
		}
		printf("%d %d\n",asum,bsum);
		scanf("%d",&n);
	}
	return 0;
}