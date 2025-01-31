#include<stdio.h>
#define N 2000
int solve(int, int);
int A[N];
int n;
int main()
{
  int m;
  int q;
  int i;
  int ans=0;

  scanf("%d",&n);
  for(i=0; i<n; i++){
    scanf("%d",&A[i]);
  }
  scanf("%d",&q);
  for(i=0; i<q; i++){
    scanf("%d",&m);
    ans = solve(m,0);
    if(ans==0) printf("no\n");
    else  printf("yes\n");
  }

  return 0;
}

int solve(int m, int i)
{
  int res;

  if(m==0) return 1;
  if(i>=n) return 0;

  res = solve(m,i+1) || solve(m-A[i],i+1);
  return res;
}