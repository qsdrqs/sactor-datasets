#include<stdio.h>
int main(void)
{
  int n,m,i,j,sum=0;
  scanf("%d %d",&n,&m);
  int a[n][m],b[m],c[n];
  for(i=0;i<n;i++)
    for(j=0;j<m;j++)
      scanf("%d",&a[i][j]);
  for(j=0;j<m;j++)
    scanf("%d",&b[j]);
  for(i=0;i<n;i++)
  {
    for(j=0;j<m;j++)
    {
      sum=sum+a[i][j]*b[j];
    }
    c[i]=sum;
    sum=0;
  }
  for(i=0;i<n;i++)
  {
    printf("%d\n",c[i]);
  }
  return 0;
}

