#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int acs(const void *a, const void *b){return *(int*)a - *(int*)b;} /* 1,2,3,4.. */
int des(const void *a, const void *b){return *(int*)b - *(int*)a;} /* 8,7,6,5.. */
int cmp_char(const void *a, const void *b){return *(char*)a - *(char*)b;} /* a,b,c,d.. */
int cmp_str(const void *a, const void *b){return strcmp(*(const char **)a, *(const char **)b);} /* aaa,aab.. */
typedef long long int lli;
typedef struct list {
  int node;
  int i;
  struct list *next;
} list;
list *graph[100001];
void initGraph(void) {
  for (int i = 0; i < 100001; i++)
    graph[i] = ((void *)0);
}
void addEdge(int node1, int node2, int i)
{
  list *new1 = (list *)malloc(sizeof(list *));
  new1->node = node2;
  new1->next = graph[node1];
  new1->i = i;
  graph[node1] = new1;
  list *new2 = (list *)malloc(sizeof(list *));
  new2->node = node1;
  new2->next = graph[node2];
  new2->i = i;
  graph[node2] = new2;
}
int color[100001] = {0};
int max = 0;
void paint(int parent, int now, int edge) {
  list *child = graph[now];
  int colors = 1;
  for (; child != ((void *)0); child = child->next) {
    if (child->node == parent) continue;
    if (colors == edge) colors++;
    color[child->i] = colors;
    paint(now, child->node, colors);
    colors++;
  }
  max = (max > colors - 1 ? max: colors - 1);
  return;
}
int main(void) {
  int n;
  scanf("%d", &n);
  initGraph();
  int a, b;
  for (int i = 1; i < n; i++) {
    scanf("%d %d", &a, &b);
    addEdge(a, b, i);
  }
  paint(0, 1, 0);
  printf("%d\n", max);
  for (int i = 1; i < n; i++) {
    printf("%d\n", color[i]);
  }
  return 0;
}
