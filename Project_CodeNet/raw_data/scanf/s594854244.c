#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_VARR_SIZE 8

typedef struct { int w, v; } edge_t;
typedef struct { int size, i; edge_t *arr; } varr_t;

static void dfs(varr_t *g, int size, int *v, int *d, int m) {
  int i, n;
  edge_t e;

  v[m] = 1;
  for (i = 0; i < g[m].i; ++i) {
    e = g[m].arr[i];
    n = e.v;
    if (v[n]) continue;
    v[n] = 1;
    d[n] = d[m] + e.w;
    dfs(g, size, v, d, n);
  }
}

static int diameter(varr_t *g, int size, int *v, int *d) {
  int max, x, i;

  dfs(g, size, v, d, 0);
  for (i = x = max = 0; i < size; ++i) {
    if (max < d[i]) {
      x = i;
      max = d[i];
    }
    v[i] = d[i] = 0;
  }
  dfs(g, size, v, d, x);
  for (i = max = 0; i < size; ++i) {
    if (max < d[i]) max = d[i];
  }
  return max;
}

int main(int argc, char **argv) {
  int n, i, k, l, *v, *d;
  varr_t *g;
  edge_t e;

  scanf("%d", &n);
  v = (int *) malloc(sizeof(int) * n);
  d = (int *) malloc(sizeof(int) * n);
  g = (varr_t *) malloc(sizeof(varr_t) * n);
  for (i = 0; i < n; ++i) {
    v[i] = d[i] = g[i].i = 0;
    g[i].size = DEFAULT_VARR_SIZE;
    g[i].arr = (edge_t *) malloc(sizeof(edge_t) * g[i].size);
  }
  for (i = 0; i < n - 1; ++i) {
    scanf("%d %d %d", &k, &l, &e.w);
    e.v = l;
    if (g[k].i == g[k].size) {
      g[k].size *= 2;
      g[k].arr = (edge_t *) realloc(g[k].arr, sizeof(edge_t) * g[k].size);
    }
    g[k].arr[g[k].i++] = e;
    e.v = k;
    if (g[l].i == g[l].size) {
      g[l].size *= 2;
      g[l].arr = (edge_t *) realloc(g[l].arr, sizeof(edge_t) * g[l].size);
    }
    g[l].arr[g[l].i++] = e;
  }
  printf("%d\n", diameter(g, n, v, d));
  for (i = 0; i < n; ++i) free(g[i].arr);
  free(g); free(v); free(d);
}
