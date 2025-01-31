
#include <stdio.h>

typedef struct _Date
{
 int year,month,day;
}Date;
int GetDay(const Date* d1, const Date* d2);
int main(void)
{
 Date d1, d2;
 while(1)
 {
  scanf("%d %d %d %d %d %d",
   &d1.year, &d1.month, &d1.day,
   &d2.year, &d2.month, &d2.day);
  if(d1.year<0 || d1.month<0 || d1.day<0 ||
   d2.year<0 || d2.month<0 || d2.day <0)
   break;
  printf("%d\n", GetDay(&d1, &d2));
 }
 return 0;
}
// Sub
int IsLeapYear(int y);
int GetMDay(int y, int m);
int GetDay(const Date* d1, const Date* d2)
{
 int dayCnt = 0;
 int y = d1->year,
  m = d1->month,
  d = d1->day;
 while(!(y==d2->year && m==d2->month && d==d2->day))
 {
  d++; dayCnt++;
  if(d>GetMDay(y,m)){m++; d=1;}
  if(m>12){y++; m=1;}
 }
 return dayCnt;
}
int IsLeapYear(int y)
{
      if(y%400 == 0)return 1;
 else if(y%100 == 0)return 0;
 else if(y%4 == 0)return 1;
 return 0;
}
int GetMDay(int y, int m)
{
 const int mday[13]={0, 31,28,31,30,31,30,31,31,30,31,30,31};
 if(m==2 && IsLeapYear(y))
  return mday[2]+1;
 return mday[m];
}
