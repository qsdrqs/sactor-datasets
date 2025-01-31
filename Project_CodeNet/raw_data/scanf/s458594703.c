#include<stdio.h>

int main(int argc, char const *argv[]) {
	long n,i,a,num=0;
	scanf("%ld",&n);
	for(i=0;i<n;i++){
		scanf("%ld",&a);
		if(a%2==1) num++;
	}
	if(num%2==1) printf("NO\n");
	else printf("YES\n");
	return 0;
}