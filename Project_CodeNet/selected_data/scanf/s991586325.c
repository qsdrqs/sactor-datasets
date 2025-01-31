#include<stdio.h>

int min(int, int);
int main(){
  unsigned int m[101][101];
  int n, p[101];
  int i, j, k,l;
  scanf("%d",&n);
  for(i=1;i<=n;i++)
    scanf("%d%d",&p[i-1],&p[i]);
  for(i=1;i<=n;i++)
    m[i][i]=0;
  for(l=2;l<=n;l++){
    for(i=1;i<=n-l+1;i++){
    j=i+l-1;
    m[i][j]=100000;
    for(k=i;k<=j-1;k++)
      m[i][j]=min(m[i][j],m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j]);
    }
  }
  printf("%d\n",m[1][n]);
  return 0;
}
int min(int x, int y)
{
  if(y<x) return y;
  return x;
}
