#include <stdio.h>

int main(void)
{
        int x,n,i,j,s,c,k=0,min=1000;
        scanf("%d%d",&x,&n);
        int p[n];
        for(i=0;i<n;i++)
                scanf("%d",&p[i]);

        c=100;
        for(i=0;i<=101;i++){
                k=0;
                for(j=0;j<n;j++)
                        if(p[j]==i) k=1;
                if(k!=1){
                        if(x>i) s=x-i;
                        else s=i-x;
                        if(min>s) { min=s; c=i;}
                        else if(min==s && c>i) c=i;
                }
        }
        printf("%d\n",c);
        return 0;
}
