#include <stdio.h>

#define MAX 10000
#define NIL -1

struct Node {int p, l, r;};
struct Node T[MAX];
int n;

/* 先行順巡回 */
void preParse(int u) {
  if(u == NIL) return;
  printf(" %d",u);
  preParse(T[u].l);
  preParse(T[u].r);
}

/* 中間順巡回 */
void inParse(int u) {
  if(u == NIL) return;
  inParse(T[u].l);
  printf(" %d",u);
  inParse(T[u].r);
}

/* 後方順巡回 */
void postParse(int u) {
  if(u == NIL) return;
  postParse(T[u].l);
  postParse(T[u].r);
  printf(" %d",u);
}

int main(void) {
  int i, v, l, r, root;
  scanf("%d",&n);
  for(i=0; i<n; i++) {
    T[i].p = NIL;
  }
  
  for(i=0; i<n; i++) {
    scanf("%d %d %d",&v,&l,&r);
    T[v].l = l;
    T[v].r = r;
    if(l != NIL) T[l].p = v;
    if(r != NIL) T[r].p = v;
  }
  
  for(i=0;i<n;i++) if(T[i].p == NIL) root = i;
  
  printf("Preorder\n");
  preParse(root);
  printf("\n");

  printf("Inorder\n");
  inParse(root);
  printf("\n");

  printf("Postorder\n");
  postParse(root);
  printf("\n");

  return 0;
}
