#include<stdio.h>
#include<string.h>

int main(void)
{
        char line[10000];
        int num;
        int i;
        char *tp;
        int a,sum,min,max;
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%d", &num);
        fgets(line, sizeof(line), stdin);
        tp = strtok( line, " ");
        sscanf(tp, "%d", &a);
        sum = a;
        min = a;
        max = a;
        while ( tp != ((void *)0)) {
                tp = strtok( ((void *)0), " ");
                if(tp != ((void *)0)) {
                        sscanf(tp, "%d", &a);
                        sum += a;
                        if( a < min) min = a;
                        if( a > max) max = a;
                }
        }
        printf("%d %d %d\n", min, max, sum);
        return 0;
}
