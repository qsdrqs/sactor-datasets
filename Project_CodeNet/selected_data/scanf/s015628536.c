#include<stdio.h>

void initialize(void);
void printQ(void);
void putqueen(int);
int row[8],col[8],dpos[2*8 -1],dneg[2*8 -1],X[8][8];
int main(){
  int i,k,r,c;
  initialize();
  scanf("%d",&k);
  for(i = 0;i < k;i++){
    scanf("%d%d",&r,&c);
    X[r][c]=-10;
  }
  putqueen(0);
  return 0;
}
void initialize() {
  int i,j;
  for(i = 0;i < 8;i++){
    row[i]=-1;
    col[i]=-1;
  }
  for(j = 0;j < 2*8 -1;j++){
    dpos[j]=-1;
    dneg[j]=-1;
  }
}
void printQ(){
  int i,j;
  for(i = 0;i < 8;i++){
    for(j = 0;j < 8;j++){
      if(X[i][j]){
        if(row[i]!=j) return;
      }
    }
  }
  for(i = 0;i < 8;i++){
    for(j = 0;j < 8;j++){
      if(row[i]==j){
        printf("Q");
      }
      else printf(".");
    }
      printf("\n");
  }
}
void putqueen(int i){
  int j;
  if(i == 8){
    printQ();
    return;
  }
  for(j = 0;j < 8;j++){
    if(col[j]==1 || dpos[i+j]==1 || dneg[i-j+8 -1]==1) continue;
    row[i]=j;
    col[j]=dpos[i+j]=dneg[i-j+8 -1]=1;
    putqueen(i+1);
    col[j]=dpos[i+j]=dneg[i-j+8 -1]=-1;
  }
}
