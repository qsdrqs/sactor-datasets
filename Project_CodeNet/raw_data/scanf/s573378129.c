#include<stdio.h>
 
int main()
{
 int x, y, box;
 scanf("%d %d", &x, &y);
  
 while((x != 0) && (y != 0)){
   if (x >= y) {
     box = x;
     x   = y;
     y   = box;
   }
 printf("%d %d\n", x, y);
 }
 return 0;
}