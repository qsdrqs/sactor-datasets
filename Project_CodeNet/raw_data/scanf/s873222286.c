#include<math.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
//用来求两数之差
double difference(double a,double b)
{
	if(a>b)
		return a-b;
	return b-a;
}
int main()
{
	
	double x1,y1,x2,y2,edge3,edge1,edge2,n,m;
	scanf("%lf %lf %lf %lf",&x1,&y1,&x2,&y2);
	edge1=difference(y1,y2);
	edge2=difference(x1,x2);
	n=edge1*edge1;
	m=edge2*edge2;
	edge3=sqrt(n+m);
	printf("%f",edge3);
	return 0;
}
