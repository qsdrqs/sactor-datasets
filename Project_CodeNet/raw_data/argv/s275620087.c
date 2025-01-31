#include <stdio.h> 
#include<stdlib.h> 
int main(int argc, char *argv[]){
    int x,y,z,i;
    int m;
    m = atoi(argv[1]);
    for(i=1;i<=m;i++){
        int count=0;
        for(x=1;x<m;x++){
            for(y=1;y<m-x;y++){
                for(z=1;z<m-x-y;z++){
                    if(x*x+y*y+z*z+x*y+y*z+z*x==i) count++;
                }
            }
        }
    printf("%d\n",count);
    }
}