#include <stdio.h>

int main(void){
  int H,W;
  scanf("%d%d",&H,&W);
  char data[H][W+1];
  for(int i = 0;i < H;i++){
    for(int j = 0;j < W+1;j++){
      scanf("%c",&data[i][j]);
    }
  }
  for(int i = 0;i < H;i++){
    for(int j = 0;j < W;j++){
      if(data[i][j] == '#'){
        if(i != 0){
          if(data[i-1][j] == '#'){
            continue;
          }
        }
        if(i != H-1){
          if(data[i+1][j] == '#'){
            continue;
          }
        }
        if(j != 0){
          if(data[i][j-1] == '#'){
            continue;
          }
        }
        if(j != W-1){
          if(data[i][j+1] == '#'){
            continue;
          }
        }
        printf("No\n");
        return 0;
      }
    }
  }
  printf("Yes\n");
  return 0;
}
