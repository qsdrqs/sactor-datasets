#include <stdio.h>

struct Node{int p, l, r;};
struct Node T[100000];
int n, D[100000];
void print(int x){
  int i,c;
  printf("node %d: parent = %d, depth = %d,  ",x,T[x].p,D[x]);
  if(T[x].p==-1)
    printf("root, ");
  else if(T[x].l==-1)
    printf("leaf, ");
  else
    printf("internal node, ");
  printf("[");
  for(i=0,c=T[x].l;c!=-1;i++,c=T[c].r){
    if(i)printf(",");
    printf(" %d",c);
  }
  printf("]\n");
}
int rec(int x, int p){
  D[x]=p;
  if(T[x].r!=-1)
    rec(T[x].r,p);
  if(T[x].l!=-1)
    rec(T[x].l,p+1);
}
int main(){
  int i,j,d,v,c,l,r;
  scanf("%d",&n);
  for(i=0;i<n;i++){
    T[i].p=T[i].l=T[i].r=-1;
  }
  for(i=0;i<n;i++){
    scanf("%d%d",&v,&d);
    for(j=0;j<d;j++){
      scanf("%d",&c);
      if(j==0) T[v].l=c;
      else T[l].r=c;
      l=c;
      T[c].p=v;
    }
  }
  for(i=0;i<n;i++){
    if(T[i].p==-1) r=i;
  }
  rec(r,0);
  for(i=0;i<n;i++){
    print(i);
  }
  return 0;
}
