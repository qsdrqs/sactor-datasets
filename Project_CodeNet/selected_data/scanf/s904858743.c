#include  <stdio.h>

int A[2000000],B[2000000],C[2000000];
void ShowData(int n)
{
  int i;
  for (i = 1; i <= n ; i++){
    printf("%d", B[i]);
    if(i<n)printf(" ");
  }
  printf("\n");
}
void CountingSort( int n)
{
  int i, j, k;
  for (i=0;i<=2000000;i++)
  C[i] = 0;
  for (j=1;j<=n;j++){
    scanf("%d",&A[j]);
    C[A[j]]++;
  }
  for (i=1;i<=2000000;i++) {
    C[i] += C[i-1];
  }
  for (j=n;j>0;j--) {
    B[C[A[j]]] = A[j];
    C[A[j]]--;
    }
}
int main(void)
{
  int i,n;
  scanf("%d",&n);
   CountingSort(n);
   ShowData(n);
  return 0;
}
