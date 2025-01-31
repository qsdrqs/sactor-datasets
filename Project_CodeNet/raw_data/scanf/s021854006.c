#include<stdio.h>

int main(){
  char name[25];
  scanf("%s",name);
  name[3]='\0';
  printf("%s",name);
}