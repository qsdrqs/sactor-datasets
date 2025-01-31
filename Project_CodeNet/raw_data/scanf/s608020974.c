#include<stdio.h>
int main(void)
{
    int m1,m2,d1,d2;

  scanf("%d %d",&m1,&m2);
  scanf("%d %d",&d1,&d2);
//  printf("flag1\n");
  if(d2-d1==1)printf("0\n");
  else printf("1\n");

  return 0;
}