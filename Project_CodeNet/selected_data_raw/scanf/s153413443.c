#include<stdio.h>
#define max 100
#define inf 200000
#define N -1
#define White 0
#define Gray 1
#define Black 2

int a[max][max];
int d[max];
int pi[max];
int color[max];
int n;

void prim(){
  int u,i,v;
  int mincost;
  for(i=0;i<n;i++){
    color[i]=White;
    d[i]=inf;
    pi[i]=N;
  }
  d[0]=0;
  while(1){
    mincost = inf;
    for(i=0;i<n;i++){
      if(color[i] != Black && d[i] < mincost){
	mincost = d[i];
	u=i;
      }
    }
    if(mincost == inf)break;

    color[u] = Black;

    for(v=0;v<n;v++){
      if(color[v]!=Black && a[u][v]!=inf){
	if(a[u][v]<d[v]){
	  d[v] = a[u][v];
	  pi[v] = u;
	  color[v]=Gray;
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
      if(a[i][j]==N)a[i][j]=inf;
    }
    color[i] = White;
    d[i]=inf;
    pi[i] = N;
  }

  prim();
  for(i=0;i<n;i++){
    if(pi[i]!=N){
      sum+=a[i][pi[i]];
    }
  }
  printf("%d\n",sum);
  return 0;
}
      
	

