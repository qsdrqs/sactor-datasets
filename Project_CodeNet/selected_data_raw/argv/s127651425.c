#include<stdio.h>
#include<stdlib.h>
int MAX_BASH = 1000;

int main(int argc, char *argv[]){
  int bash[MAX_BASH];
  int i, j, temp, top, second, third;
  bash[0]=atoi(argv[1]);
  for(i=1; i<argc-1; i++){
    bash[i]=atoi(argv[i+1]);
  }
  for(i=0; i<10; i++){
    for(j=i+1; j<10; j++){
      if(bash[i]<=bash[j]){
        temp = bash[i];
        bash[i] = bash[j];
        bash[j] = temp;
      }
    }
  }
  top = bash[0];
  second = bash[1];
  third = bash[2];
  printf("%d\n",top);
  printf("%d\n",second);
  printf("%d\n",third);
  return 0;
}