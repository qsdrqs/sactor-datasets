#include<stdio.h>

int main(void)
{
int A,B,K;

scanf("%d%d",&A,&B);

if(A<0) A = A*(-1);
if(B<0) B = B*(-1);

K=(A+B)/2;

if((A+B)%2==0)

printf("%d",K);

else
printf("IMPOSSIBLE");

return 0;
}
