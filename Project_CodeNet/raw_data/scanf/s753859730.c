#include<stdio.h>
int main()
{
    int a,b,c,d,e,i;
    scanf("%d",&a);
    for(i=0;i<a;i++){
        scanf("%d",&b);
        if(i==0)c=2000000000;
        d=b-c;
        if(b<c)c=b;
        if(i==0)e=d;
        if(d>e)e=d;
    }
    printf("%d\n",e);
    return 0;
}