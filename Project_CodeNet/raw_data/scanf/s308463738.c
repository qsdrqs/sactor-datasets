#include<stdio.h>

#define Max 10000
#define NIL -1

typedef struct Node{
  int parent, l, r;
}Node;

Node T[Max];
int n, D[Max], H[Max];

void setDepth(int u, int d){
  if(u == NIL) return;
  D[u] = d;
  setDepth(T[u].l, d + 1);
  setDepth(T[u].r, d + 1);
}

int setHeight(int u){
  int h1 = 0, h2 = 0;

  if(T[u].l != NIL) h1 = setHeight(T[u].l) + 1;
  if(T[u].r != NIL) h2 = setHeight(T[u].r) + 1;
  return H[u] = (h1 > h2 ? h1 : h2);
}


int getSibling(int u){
  if(T[u].parent == NIL) return NIL;
  if(T[T[u].parent].l != u && T[T[u].parent].l != NIL) return T[T[u].parent].l;
  if(T[T[u].parent].r != u && T[T[u].parent].r != NIL) return T[T[u].parent].r;

  return NIL;
}

void print(int u){
  printf("node %d: ", u);
  printf("parent = %d, ", T[u].parent);
  printf("sibling = %d, ", getSibling(u));
  int deg = 0;
  if(T[u].l != NIL) deg++;
  if(T[u].r != NIL) deg++;
  printf("degree = %d, ", deg);
  printf("depth = %d, ", D[u]);
  printf("height = %d, ", H[u]);

  if(T[u].parent == NIL){
    printf("root\n");
  }
  else if(T[u].l == NIL && T[u].r == NIL){
    printf("leaf\n");
  }
  else{
    printf("internal node\n");
  }
}


int main(){
  int i, v, l, r, root = 0;

  scanf("%d", &n);
  for(i = 0 ; i < n ; i++) T[i].parent = NIL;

  for(i = 0 ; i < n ; i++){
    scanf("%d %d %d", &v, &l, &r);
    T[v].l = l;
    T[v].r = r;
    if(l != NIL) T[l].parent = v;
    if(r != NIL) T[l].parent = v;
  }

  for(i = 0 ; i < n ; i++){
    if(T[i].parent == NIL) root = i;
  }

  setDepth(root, 0);
  setHeight(root);

  for(i = 0 ; i < n ; i++) print(i);

  return 0;
}
