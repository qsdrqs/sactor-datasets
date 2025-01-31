#include <stdio.h>
#include <math.h>

typedef struct {
  double x;
  double y;
}data;
void kock(int,data,data);
int main(){
  int n;
  data a;
  data b;
  scanf("%d",&n);
  a.x=0;
  a.y=0;
  b.x=100;
  b.y=0;
    printf("%.8f,%.8f\n",a.x,a.y);
    kock(n,a,b);
  printf("%.8f,%.8f\n",b.x,b.y);
  return 0;
}
void kock(int n,data p1,data p2){
  data s,t,u;
  double x=1.57079632679489661923*2/3;
  if(n==0) return;
  s.x=(2.0*p1.x+1.0*p2.x)/3.0;
  s.y=(2.0*p1.y+1.0*p2.y)/3.0;
  t.x=(1.0*p1.x+2.0*p2.x)/3.0;
  t.y=(1.0*p1.y+2.0*p2.y)/3.0;
  u.x=(t.x-s.x)*cos(x)-(t.y-s.y)*sin(x)+s.x;
  u.y=(t.x-s.x)*sin(x)+(t.y-s.y)*cos(x)+s.y;
  kock(n-1,p1,s);
  printf("%.8f,%.8f\n",s.x,s.y);
  kock(n-1, s, u);
  printf("%.8f,%.8f\n",u.x,u.y);
  kock(n-1, u, t);
  printf("%.8f,%.8f\n",t.x,t.y);
  kock(n-1, t, p2);
}
