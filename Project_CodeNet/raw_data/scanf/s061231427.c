#include <stdio.h>

int main(void) {
	int a, b, c, n, x, sum;
	
	while(1){
		scanf("%d %d", &n, &x);
		
		sum=0;
		
		if(n==0 && x==0)
		break;
		
		for(a=1;a<=n-2;a++){
			for(b=a+1;b<=n-1;b++){
				for(c=b+1;c<=n;c++){
					if(a+b+c==x)
					sum+=1;
				}
			}
		}
		
		printf("%d\n", sum);
	}
	
	return 0;
}