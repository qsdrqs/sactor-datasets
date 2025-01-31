#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
  int prime_num[100000] = {};
  int S[100000] = {};
  int a[100000] = {};
  int ans[100000] = {};
  int l, r, i, j;
  int Q; scanf("%d", &Q);
  // hurui
  prime_num[0] = 1;
  prime_num[1] = 1;
  for(i = 2; i < 100000; i++){
    if(prime_num[i] == 1) continue;
    else{
      for(j = i * 2; j < 100000 / j; j += i){
 prime_num[j] = 1;
      }
    }
  }
  // like 2017
  for(i = 0; i < 100000; i++){
    if(prime_num[i] == 1) continue;
    else{
      if(prime_num[i] == 0 && prime_num[(i + 1)/ 2] == 0) a[i] = 1;
    }
  }
  // ruiseki wa
  S[0] = 0;
  /* for(i = 0; i < MAX; i++){ */
  /*   for(j = 0; j < i; j++){ */
  /*     if(i != 0) S[i] += a[j]; */
  /*   } */
  /* } */
  for(i = 0; i < 100000; i++) S[i + 1] = S[i] + a[i];
  for(i = 0; i < Q; i++){
    scanf("%d", &l);
    scanf("%d", &r);
    r++;
    ans[i] = S[r] - S[l];
  }
  for(i = 0; i < Q; i++){
    printf("%d\n", ans[i]);
  }
  return 0;
}
