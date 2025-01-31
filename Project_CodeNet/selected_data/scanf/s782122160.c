#include <stdio.h>
#include <limits.h>

int main(void) {
 long long int a[1000][1000];
 long long int b[1000][1000];
 long long int c[1000][1000];
 int n,m,l;
 scanf("%d%d%d",&n,&m,&l);
 for(int i = 0; i < n; i++){
  for(int j = 0; j < m; j++){
   scanf("%lld",&a[i][j]);
  }
 }
 for(int i = 0; i < m; i++){
  for(int j = 0; j < l; j++){
   scanf("%lld",&b[i][j]);
  }
 }
 for(int i = 0; i < n; i++){
  for(int j = 0; j < l; j++){
   c[i][j] = 0;
   for(int k = 0; k < m; k++){
    c[i][j] += a[i][k] * b[k][j];
   }
  }
 }
 for(int i = 0; i < n; i++){
  printf("%lld",c[i][0]);
  for(int j = 1; j < l; j++){
   printf(" %lld",c[i][j]);
  }
  printf("\n");
 }
 return 0;
}
