#include <stdio.h>
#include <string.h>

int main(void){
  char mozi[201], cpmz[201];
  int i=0, j, cnt, p; //cnt シャッフル回数
  int len;
  while(1){
    scanf("%s\n%d", mozi, &cnt);
    if(!strcmp(mozi, "-")) break;
    len = strlen(mozi);
    while(i<cnt){
      scanf("%d", &p);
      for(j=0; j<p; j++)
        cpmz[j+len-p] = mozi[j];
      for(j=p; j<len; j++)
        cpmz[j-p] = mozi[j];
      i++;
    }
    printf("%s\n", mozi);
  }
  return 0;
}
