#include <stdio.h>

int main(){
  int H, W;
  scanf("%d %d",&H ,&W);
  int i, j;
  while(1){
    if(H == 0 && W == 0){
      break;
    }
    else if(H == 0){
      for(i = 0; i < W; ++i){
        printf("#");
      }
      printf("\n");
    }
    else if(W == 0){
      for(i = 0; i < H; ++i){
        printf("#\n");
      }
    }
    else{
      for(i = 0; i < H; ++i){
        for (int j = 0; j < W; ++j) {
          printf("#");
        }
        printf("\n");
      }
    }
    scanf("%d %d",&H ,&W);
  }
  return 0;
}
