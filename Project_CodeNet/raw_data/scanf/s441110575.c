#include <stdio.h>
int main(void){
	int q,p,n,l,r;
	char c;
	scanf("%d",&q);
	l=r=0;
	while(q--){
		scanf("%d %c %d",&p,&c,&n);
		if(c=='('){
			l+=n;
		}
		else{
			r+=n;
		}
		printf("%s\n",l==r?"YES":"NO");
	}
	return 0;
}