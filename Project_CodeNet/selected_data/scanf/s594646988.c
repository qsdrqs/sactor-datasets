#include <stdio.h>

typedef struct List {
 struct List *next;
 int v;
} list;
int main()
{
 int i, N, K, a[100001];
 scanf("%d %d", &N, &K);
 for (i = 1; i <= N; i++) scanf("%d", &(a[i]));
 int ans = 0;
 if (a[1] != 1) {
  a[1] = 1;
  ans++;
 }
 list *adj[100001], e[100001];
 for (i = 2; i <= N; i++) {
  e[i].v = i;
  e[i].next = adj[a[i]];
  adj[a[i]] = &(e[i]);
 }
 int height[100001] = {}, q[100001], head, tail;
 list *p;
 q[0] = 1;
 for (head = 0, tail = 1; head < tail; head++) {
  for (p = adj[q[head]]; p != ((void *)0); p = p->next) q[tail++] = p->v;
 }
 for (head--; head > 0; head--) {
  i = q[head];
  if (height[i] == K - 1 && a[i] != 1) {
   height[i] = -1;
   a[i] = 1;
   ans++;
  }
  if (height[a[i]] < height[i] + 1) height[a[i]] = height[i] + 1;
 }
 printf("%d\n", ans);
 fflush(stdout);
 return 0;
}
