#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

int main(int argc,char *argv[]){
    int i;
    float result;
    float num = atof(argv[1]);
    _Bool flag = 0;
    if ((int)num == 1){
        printf("1");
        return 0;
    }
    if (( (int)num & 1 ) == 1){
        flag = 1;
    }
    i = num / 2 ;
    if(flag == 1){
        i = i + 1;
    }
    result = i / num;
  printf("%f¥n",result);
}
