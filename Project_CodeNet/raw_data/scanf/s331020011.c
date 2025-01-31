#include <stdio.h>

int main(){
    int a,b,c,d,e,f,h;

 
    scanf("%d", &a);
    scanf("%d", &b);
    
	c = a + b;
    d = a - b;
    e = a * b;
    h = (f = c,d,e);
    

	if((c>=d) && (c>=e)){
	
	f=c;	

	}

	
	if((d>=c) && (d>=e)){
	f=d;

	}

		
	if((e>=d) && (e>=c)){
	f=e;

}

	printf("%d",f);


	
	
	return 0 ;
	
}