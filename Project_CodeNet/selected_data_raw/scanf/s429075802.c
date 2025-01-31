#include <stdio.h>
 
int main(){
 
   int a[10000];
   int i, n, max, min;
   long int b = 0;
 
   scanf("%d", &n);
   for (i = 0; i < n; i++){
      scanf("%d", &a[i]);
      b = b + a[i];
   }
 
   max = a[0];
   min = a[0];
 
   for (i = 0; i < n; i++){
      if (max < a[i]){
         max = a[i];
      }
      if (min > a[i]){
         min = a[i];
      }
   }
 
   printf("%d %d %ld\n", min, max, b);
 
   return 0;
 
}