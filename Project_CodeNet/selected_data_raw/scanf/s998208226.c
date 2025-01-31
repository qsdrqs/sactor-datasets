#include <stdio.h>
#include <string.h>
#define rep(i,l,n) for(i=l;i<n;i++)

char change(char n){
	if(n>='A' && n<='Z') return n+'a'-'A';
	else return n;
}


int main(void){
	char w[11];
	int i,len,ans=0;
	
	scanf("%s",w);
	
	
	while(1){
		char t[1001];
		scanf("%s",t);
		if(strcmp(t,"END_OF_TEXT")==0) break;
		
		len=strlen(t);
		
		rep(i,0,len){
			t[i]=change(t[i]);
		}
		
		
		if(strcmp(t,w)==0) ans++;
	}
	printf("%d\n",ans);
	
	return 0;
}