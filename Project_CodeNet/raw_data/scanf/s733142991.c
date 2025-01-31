
#include<stdio.h>
int main()
{
    int m,f,r,t;
    for(;;)
    {
        scanf("%d%d%d",&m,&f,&r);
        t=m+f;
        if(m+f+r==-3)return 0;
        if(m==-1||f==-1)puts("F");
        else if(t>=80)puts("A");
        else if(t>=65)puts("B");
        else if(t>=50||r>=50)puts("C");
        else if(t>=30)puts("D");
        else puts("F");
    }
    return 0;
}
