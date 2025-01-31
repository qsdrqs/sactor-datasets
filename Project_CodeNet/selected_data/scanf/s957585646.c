#include <stdio.h>

int main(){
  int i, j, minj, count = 0, n, tmp, a[100];
  scanf("%d", &n);
  for(i = 0; i < n; i++){
    scanf("%d", &a[i]);
  }
  for(i = 0; i < n; i++){
    minj = i;
    for(j = i; j < n; j++){
      if(a[j] < a[minj]){
 minj = j;
      }
    }
    if(i != minj){
      tmp = a[i];
      a[i] = a[minj];
      a[minj] = tmp;
      count++;
    }
  }
  for(i = 0; i < n; i++){
    printf("%d", a[i]);
    if(i != n-1) printf(" ");
  }
  printf("\n%d\n", count);
  return 0;
}
