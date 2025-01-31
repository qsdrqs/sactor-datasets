#include<stdio.h>

int f(int num){
  int i;
  if(num == 3 || num == 2){
    return 1;
  }
  if(!(num % 2)){
    return 0;
  }
  for(i = 3; i < num; i+=2){
    if(!(num % i)){
      return 0;
    }
  }
  return 1;
}

int main(void){
  int q, result[100000] = {};
  int i, j, k;
  int low, high;
  
  scanf("%d", &q);
  for(k = 0; k < q; k++){
    scanf("%d%d", &low, &high);
    if(low == 1){
      low += 2;
    }
    for(i = low; i <= high; i += 2){
      result[k] += (f(i) && f((i + 1) / 2));
    }
  }

  for(i = 0; i < q; i++){
    printf("%d\n", result[i]);
  }

  return 0;
}