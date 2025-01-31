#include <stdio.h>
#define N 100

int main(){
  int i,j,n,u,k,v,V[N+1][N+1];

  scanf("%d",&n);
  for(i=1;i<=n;i++){
    for(j=1;j<=n;j++){
      V[i][j] = 0;
    }
  }
  for(i=1;i<=n;i++){
    scanf("%d%d",&u,&k);
    for(j=0;j<k;j++){
      scanf("%d",&v);
      V[u][v] = 1;
    }
  }
  for(i=1;i<=n;i++){
    for(j=1;j<=n;j++){
      if(j != n){
	if(V[i][j] != 1)
	  printf("%d ",V[i][j]);
	else printf("%d ",V[i][j]);
      }
      else {
	if(V[i][j] != 1)
	  printf("%d",V[i][j]);
	else printf("%d",V[i][j]);
      }
    }
    printf("\n");
  }

return 0;
}

