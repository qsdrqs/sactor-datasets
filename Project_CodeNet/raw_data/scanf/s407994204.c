
#include <stdio.h>

int main()
{
    int i;
   char a[101];
  scanf("%s",a);
   for(i=0;i<=3;i++)
   {
       printf("%c",a[i]);
   }
   printf(" ");
   for(i=4;i<=12;i++)
   {
       printf("%c",a[i]);
   }
    return 0;
}