#include <stdio.h>
#include <math.h>

int main(void)
{
   int i,m, f, r;
    for(i=0; i<50; i++){
    scanf("%d %d %d", &m, &f, &r);
    if(m == -1 && f == -1 && r == -1) break;
    if(m==-1 || f==-1 || m+f<=30)
    printf("F\n");
        else if(m+f>=80)
            printf("A\n");
        else if(m+f>=65 && m+f<80)
            printf("B\n");
        else if(m+f>=50 && m+f<65)
            printf("C\n");
        else if(m+f>=30 && m+f<50)
            printf("D\n");
        else if(r>=50)
            printf("C\n");
    }
    return 0;
}
