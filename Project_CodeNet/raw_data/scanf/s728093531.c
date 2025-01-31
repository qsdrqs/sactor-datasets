#include<stdio.h>

int main(void){
  char str[100002];
  scanf("%100001s",str);
  int array[]={-1,1};
  int i,j;

  //文字列の長さ
  for(j=0;str[j]!='\0';j++){
  }

  for(i=0;i<j;i++){
    if(str[i]==str[i+1]){
      array[0]=i+1,array[1]=i+2;
      // printf("%d %d\n",array[0],array[1]);
      break;
    }else if(str[i]==str[i+2]){
      array[0]=i+1,array[1]=i+3;
      //printf("%d %d\n",array[0],array[1]);
      break;
    }
  }

  // printf("%d\n",j);
  printf("%d %d\n",array[0],array[1]);
    return 0;
  }
