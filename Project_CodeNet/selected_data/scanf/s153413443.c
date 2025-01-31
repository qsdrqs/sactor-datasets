#include<stdio.h>

int a[100][100];
int d[100];
int pi[100];
int color[100];
int n;
void prim(){
  int u,i,v;
  int mincost;
  for(i=0;i<n;i++){
    color[i]=0;
    d[i]=200000;
    pi[i]=-1;
  }
  d[0]=0;
  while(1){
    mincost = 200000;
    for(i=0;i<n;i++){
      if(color[i] != 2 && d[i] < mincost){
 mincost = d[i];
 u=i;
      }
    }
    if(mincost == 200000)break;
    color[u] = 2;
    for(v=0;v<n;v++){
      if(color[v]!=2 && a[u][v]!=200000){
 if(a[u][v]<d[v]){
   d[v] = a[u][v];
   pi[v] = u;
   color[v]=1;
 }
      }
    }
  }
}
int main(){
  int i,j,sum=0;
  scanf("%d",&n);
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      scanf("%d",&a[i][j]);
      if(a[i][j]==-1)a[i][j]=200000;
    }
    color[i] = 0;
    d[i]=200000;
    pi[i] = -1;
  }
  prim();
  for(i=0;i<n;i++){
    if(pi[i]!=-1){
      sum+=a[i][pi[i]];
    }
  }
  printf("%d\n",sum);
  return 0;
}
