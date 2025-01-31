#include<stdio.h>
int main(void){
char ch;
int counter[26],i;
	for(i=0;i<=25;i++){
        counter[i]=0;
	}
	while(scanf("%c",&ch)!=EOF){
	  if('A'<=ch && ch<='Z'){
	    ch=ch+('a'-'A');
	  }
	  if('a'<=ch && ch<='z'){
	    counter[ch-'a']++;
	}
	}
for(i=0;i<=25;i++){
	printf("%c : %d\n",'a'+i,counter[i]);
}

return(0);
}
