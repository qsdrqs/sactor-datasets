#include<stdio.h>
#include<string.h>

#define MAX_LENGTH 10000

int main(void)
{
        char line[MAX_LENGTH];
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

        while ( tp != NULL) {
                tp = strtok( NULL, " ");
                if(tp != NULL) {
                        sscanf(tp, "%d", &a);
                        sum += a;
                        if( a < min) min = a;
                        if( a > max) max = a;
                }
        }

        printf("%d %d %d\n", min, max, sum);

        return 0;
}