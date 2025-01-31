#include <stdio.h>
int main(void){
    char a,c;
    int n,b,i,j,k;
    int cards[4][13];
    
    scanf("%d",&n);
    for(k=1;k<=n;k++){
        scanf("%c",&c);
        scanf("%c %d",&a,&b);
        if(a=='S') i=0;
        if(a=='H') i=1;
        if(a=='C') i=2;
        if(a=='D') i=3;
        
        cards[i][b-1]=1;
    }
    
    for(i=0;i<4;i++){
        for(j=0;j<13;j++){
            if(cards[i][j]!=1){
               if(i==0) printf("S %d\n",j+1);
               if(i==1) printf("H %d\n",j+1);
               if(i==2) printf("C %d\n",j+1);
               if(i==3) printf("D %d\n",j+1);
               
            }
        }
    }
    return 0;
}

