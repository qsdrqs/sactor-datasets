#include <stdio.h>
int main(void){
    int n,a,x[100001],i;
    scanf("%d", &n);
    for(i=1; i<=n; i++)
    {
        scanf("%d", &a);
        x[a]=i;
    }
    for(i=1; i<=n; i++)
    {
        printf("%d", x[i]);
        if(i<n)
        printf(" ");
    }
    printf("\n");
    
    return 0;
}