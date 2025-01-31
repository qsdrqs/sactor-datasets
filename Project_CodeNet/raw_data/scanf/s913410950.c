// Ver19.03
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INF (1 << 29) * 2
#define LLINF 4545454545454545454
#define MOD 1000000007
#define ll long long
#define ull unsigned long long
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
int upll(const void *a, const void *b) { return *(ll *)a < *(ll *)b ? -1 : *(ll *)a > *(ll *)b ? 1 : 0; }
int downll(const void *a, const void *b) { return *(ll *)a < *(ll *)b ? 1 : *(ll *)a > *(ll *)b ? -1 : 0; }
void sortup(ll *a, int n) { qsort(a, n, sizeof(ll), upll); }
void sortdown(ll *a, int n) { qsort(a, n, sizeof(ll), downll); }

int p[100000];
int par[100000];

int root(int x)
{
  if (par[x] == x)
    return x;
  return par[x] = root(par[x]);
}

void unite(int x, int y)
{
  int rx = root(x);
  int ry = root(y);
  if (rx != ry)
    par[rx] = ry;
}

int same(int x, int y)
{
  int rx = root(x);
  int ry = root(y);
  return rx == ry;
}

int main()
{
  int n, m, ans = 0;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    scanf("%d", p + i);
  for (int i = 0; i < n; i++)
    par[i] = i;
  for (int i = 0; i < m; i++)
  {
    int x, y;
    scanf("%d%d", &x, &y);
    unite(x, y);
  }
  for (int i = 1; i <= n; i++)
  {
    if (same(i, p[i]))
      ans++;
  }
  printf("%d\n", ans);
  return 0;
}