#include <stdio.h>

int main(void){

   int n, x, i, j, k, num = 0, count = 0;

   while (x!=0 && n!=0) {

      scanf("%d %d", &n, &x);

      for (i = 1; i <= n; i++) {
         num = 0;
         num += i;
         for (j = 1; j <= n; j++) {
            num += j;
            for (i = k; k <= n; k++) {
               num += k;
               if (num = x) {
                  count++;
               }
            }
         }
      }
   }

   printf ("%d\n", count);

   return(0);

}


