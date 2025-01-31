#include <stdio.h>

int main(){

  int i;
  int N;
  int K;

  scanf("%d %d", &N, &K);
  int h[N];

  for(i = 1; i <= N; i++){

    scanf("%d", &h[i - 1]);
  }

  int count = 0;

  for(i = 1; i <= N; i++){

    if(h[i - 1] >= K){
      count++;
    }
  }

  printf("%d", count);

  return 0;
}