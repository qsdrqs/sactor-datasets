#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[]){
int contest = strlen(argv[1]);
    if(argc = 2 && 1<= contest <=4){
        if(contest<4){
            printf("ABC\n");
        }else{
            printf("ABD\n");
        }
    }else{
        printf("1≤N≤1998\n");
    }
}
