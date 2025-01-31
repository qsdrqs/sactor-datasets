/* valime0 - 10 */
#include <stdio.h>
#include <math.h>

int main(void)
{
 double x1,x2,x3,y1,y2,y3,a,a2,b,b2,c,c2,num,num2,h1,h2,h3,s,ans,k,j;
 int i,n;
 scanf("%d",&n);
 for(i = 0; i < n; i++){
  scanf("%lf %lf %lf %lf %lf %lf",&x1,&y1,&x2,&y2,&x3,&y3);
  a = fabs(2 * (x2 - x1));
  b = fabs(2 * (y2 - y1));
  c = fabs((x1 * x1) - (x2 * x2) + (y1 * y1) - (y2 * y2));
  a2 = fabs(2 * (x3 - x1));
  b2 = fabs(2 * (y3 - y1));
  c2 = fabs((x1 * x1) - (x3 * x3) + (y1 * y1) - (y3 * y3));
  num = fabs((b * c2 - b2 * c)/(a * b2 - a2 *b));
  num2 = fabs((c * a2 - c2 * a)/(a * b2 - a2 * b));
  //num = num + 0.0005;
  //num2 = num2 + 0.0005;
  /*if(x1 == x2){
			h1 = fabs(y1 - y2);
		}else if(y1 == y2){
			h1 = fabs(x1 - x2);
		}else{
			k = fabs(y1 - y2);
			j = fabs(x1 - x2);
			h1 = sqrt(((k*k) + (j*j)));
		}
		
		if(x2 == x3){
			h2 = fabs(y2 - y3);
		}else if(y2 == y3){
			h2 = fabs(x2 - x3);
		}else{
			k = fabs(y2 - y3);
			j = fabs(x2 - x3);
			h2 = sqrt(((k*k) + (j*j)));
		}*/
  if(num == x3){
   h3 = fabs(num2 - y3);
  }else if(num2 == y3){
   h3 = fabs(num - x3);
  }else{
   k = fabs(num2 - y3);
   j = fabs(num - x3);
   h3 = sqrt(((k*k) + (j*j)));
   //h3 = h3 + 0.0005;
  }
  /*s =(h1 + h2 + h3) * 0.5;
		ans = sqrt( s * (s - h1) * (s - h2) * (s - h3));*/
  printf("%.3lf %.3lf %.3lf\n",num,num2,h3);
 }
 return 0;
}
