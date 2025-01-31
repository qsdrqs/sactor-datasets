#include<stdio.h>
#include<stdlib.h>

#define MIN 1
#define MAX 100
   
int main(int argc, char *argv[])
{

    int x = atoi(argv[1]);

    if(x < MIN || x > MAX){
        return -1;
    }
  
    printf("%d\n" , x*x*x);
   
    return 0;
}
