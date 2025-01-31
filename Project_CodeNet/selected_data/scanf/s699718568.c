#include <stdio.h>

int main(void){
    int i,n,b,r,f,v,j,k;
    int tower[100][100][100];
    scanf("%d",&n);
    for(i=1;i<=3;i++){
        scanf("%d %d %d %d ",&b,&r,&f,&v);
        tower[b][r][f]=v;
    }
    for(i=1;i<=4;i++){
        for(j=1;j<=3;j++){
            for(k=1;k<=10;k++){
                if(tower[i][j][k]>=1){
                        printf(" %d",tower[i][j][k]);
                }
                else if(i==4||j==3||k==10){
                    printf(" 0");
                }
                else{
                    printf(" 0");
                }
            }
            printf(" \n");
        }
        if(i==4){
            printf("\n");
        }
        else{
            printf("#################### \n");
        }
    }
}
