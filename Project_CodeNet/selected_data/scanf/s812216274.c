#include <stdio.h>

int main(void)
{
 int n;
 int num[1000];
 int i;
 int j;
 int swap;
 scanf("%d", &n);
 for (i = 0; i < n; i++){
  scanf("%d", &num[i]);
 }
 for (i = 0; i < n - 1; i++){
  for (j = 0; j < n - 1; j++){
   if (num[j] > num[j + 1]){
    swap = num[j];
    num[j] = num[j + 1];
    num[j + 1] = swap;
   }
  }
 }
 for (i = 0; i < n; i++){
  printf("%d", num[i]);
  if (i != n - 1){
   printf(" ");
  }
  else {
   printf("\n");
  }
 }
 return 0;
}
