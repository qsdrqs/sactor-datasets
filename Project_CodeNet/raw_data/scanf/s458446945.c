#include<stdio.h>
#define N 3
int main(){
    char str[N+1]={0};
    int mxchain=0,i=0,j=0;
    scanf("%s",str);
    for(i=0;i<N;i++){
        if(str[i]=='R')j++;
        if(str[i]=='S'){
            if(j>mxchain)mxchain=j;
            j=0;
        }
    }
    return 0;
}
