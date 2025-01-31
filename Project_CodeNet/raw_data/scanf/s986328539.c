#include<stdio.h>
int main(void)
{
	int n,l[4],s[4],a,b,c,d,e;
	scanf("%d",&n);
	while(n!=0000){
		int f=0;
		b=0;
		while(n!=6174){
			l[0]=n/1000;
			l[1]=n/100-l[0]*10;
			l[2]=n/10-(l[0]*100+l[1]*10);
			l[3]=n-(l[0]*1000+l[1]*100+l[2]*10);
			if(l[0]==l[1]&&l[1]==l[2]&&l[2]==l[3]){
				printf("NA\n");
				f=1;
				break;
			}
			for(c=0;c<4;c++){
				for(d=c+1;d<4;d++){
					if(l[c]<l[d]){
						e=l[c];
						l[c]=l[d];
						l[d]=e;
					}
				}
			}
			for(c=0;c<4;c++){
				s[c]=l[3-c];
			}
			n=(l[0]*1000+l[1]*100+l[2]*10+l[3])-(s[0]*1000+s[1]*100+s[2]*10+s[3]);
			b=b+1;
		}
		if(f!=1){
		printf("%d\n",b);
		}
		scanf("%d",&n);
	}
	return 0;
}