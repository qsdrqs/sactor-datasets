#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{
 int i, j, len;
 int flag = 0;
 char *input;
 input = argv[1];
 len = strlen(input);
 for (i = 1; i < len; i++) {
  for (j = i + 1; j < len; j++) {
   if (input[i] == input[j]) {
    printf("no");
    exit(0);
   }
  }
 }
 printf("yes");
 return(0);
}
