#include<stdio.h>

#define N 8
#define FREE -1
#define NFREE 1
#define EXIST -10
void initialize(void);
void printQ(void);
void putqueen(int);

int row[N],col[N],dpos[2*N-1],dneg[2*N-1],X[N][N];

int main(){
  int i,k,r,c;
  initialize();
  scanf("%d",&k);
  for(i = 0;i < k;i++){
    scanf("%d%d",&r,&c);
    X[r][c]=EXIST;
  }
  putqueen(0);
  return 0;
}

void initialize() {
  int i,j;
  for(i = 0;i < N;i++){
    row[i]=FREE;
    col[i]=FREE;
  }
  for(j = 0;j < 2*N-1;j++){
    dpos[j]=FREE;
    dneg[j]=FREE;
  }
}

void printQ(){
  int i,j;
  for(i = 0;i < N;i++){
    for(j = 0;j < N;j++){
      if(X[i][j]){
        if(row[i]!=j) return;
      }
    }
  }
  for(i = 0;i < N;i++){
    for(j = 0;j < N;j++){
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
  if(i == N){
    printQ();
    return;
  }
  for(j = 0;j < N;j++){
    if(col[j]==NFREE || dpos[i+j]==NFREE || dneg[i-j+N-1]==NFREE) continue;
    row[i]=j;
    col[j]=dpos[i+j]=dneg[i-j+N-1]=NFREE;
    putqueen(i+1);
    col[j]=dpos[i+j]=dneg[i-j+N-1]=FREE;
  }
}