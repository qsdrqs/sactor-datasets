#include<stdio.h>

int main(void) {
int i = 1;
int num;
scanf("%d", &num);

while(num != 0) {
printf("Case %d: %d\n", i, num);
i++;
scanf("%d", &num);
}

return (0);
}