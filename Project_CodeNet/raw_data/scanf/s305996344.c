#include<stdio.h>
int main(){
  int x,y;
  int n;
  for(n = 0;n < 3001;n++){
    scanf("%d %d",&x,&y);
    if (x == 0 && y == 0) break;
    else if (x < y){
      printf("%d %d\n",x,y);
    }else if(x > y){
      printf("%d %d\n",y,x);
    }
    return 0;
  }
}

