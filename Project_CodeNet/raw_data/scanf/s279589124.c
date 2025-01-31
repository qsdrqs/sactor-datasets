#include<stdio.h>
 
int main()
{
  int i,j,k,N,wmax,hmax,count,flag;
  int d[200]={0},n[200]={0};
  int board[401][401];
  
  while(scanf("%d",&N),N){
count=0;
    
    for(i=0;i<401;i++){
      for(j=0;j<401;j++){
        board[i][j]=-1;
      }
    }
    board[200][200]=0;
    
    for(i=1;i<N;i++){
      scanf("%d%d",&n[i],&d[i]);
    }
    
    for(k=1;k<N;k++){
      for(i=0;i<401;i++){
        for(j=0;j<401;j++){
          if(board[i][j]==n[k]){
            switch(d[k]){
              case 0:
              board[i][j-1]=k;
              break;
              case 1:
              board[i+1][j]=k;
              break;
              case 2:
              board[i][j+1]=k;
              break;
              case 3:
              board[i-1][j]=k;
              break;
            }
          }
        }
      }
    }
    
          wmax=0;
    for(i=0;i<401;i++){
flag=0;
      for(j=0;j<401;j++){
        if(board[i][j]>-1){
          for(k=400;k>=0;k--){
            if(board[i][k]>-1){
              count=k-j+1;
flag=1;
break;
            }
          }
        }
if(flag) break;
        if(wmax<count) wmax=count;
      }
    }
          hmax=0;
count=0;
    for(i=0;i<401;i++){
flag=0;
      for(j=0;j<401;j++){
        if(board[j][i]>-1){
          for(k=400;k>=0;k--){
            if(board[k][i]>-1){
              count=k-j+1;
flag=1;
              break;
            }
          }
        }
if(flag) break;
        if(hmax<count) hmax=count;
      }
    }
    printf("%d %d\n",wmax,hmax);
  }
  return 0;
}