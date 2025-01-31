#include<stdio.h>
int main()
{
    int a,b,c,d,y,n;
    scanf("%d %d %d %d",&a,&b,&c,&d);
    y=a/d;
    n=c/b;
    if(a%d!=0)y++;
    if(c%b!=0)n++;
    if(y<n){
        printf("No\n");
    }else{
        printf("Yes\n");
    }
    return 0;
}