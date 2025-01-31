#include  <stdio.h>
#define MAX 2000000

int A[MAX],B[MAX],C[MAX];

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

  for (i=0;i<=MAX;i++)
  C[i] = 0;


  for (j=1;j<=n;j++){
    scanf("%d",&A[j]);
    C[A[j]]++;

  }
  for (i=1;i<=MAX;i++) {
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
