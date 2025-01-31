#include<stdio.h>

int main(void)
{
  int a=0, m=0, r=0, c=0, h=0,i,num;
  long answer;
  scanf("%d", &num);
  char array[10];
  for(i=1; i<=num; i++)
  {
    scanf("%s", &array);
    if(array[0]=='M')m++;
    if(array[0]=='A')a++;
    if(array[0]=='R')r++;
    if(array[0]=='C')c++;
    if(array[0]=='H')h++;
  }
  
   answer=m*a*r+m*a*c+m*a*h+m*r*c+m*r*h+m*c*h+a*r*c+a*c*h+r*c*h+a*r*h;
   printf("%d", answer);
  
  return 0;
}
