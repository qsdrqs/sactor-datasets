#include <stdio.h>
 
int main(void) {
    int i,j,k,n,b,f,r,v,p[4][3][10]={0};
    char fence[]="####################";
    scanf("%d",&n);
    while (n--){
        scanf("%d %d %d %d",&b,&f,&r,&v);
        p[b-1][f-1][r-1]+=v;
    }
    for (i=0;i<4;i++){
        for (j=0;j<3;j++){
            for (k=0;k<10;k++){
                printf(" %d",p[i][j][k]);
            }
            printf("%c",'\n');
        }
        if (i!=3) printf("%s\n",fence);
    }
    return 0;
}
