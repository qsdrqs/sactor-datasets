#include <stdio.h>
#include <stdlib.h>


int main()
{

        int n, m;
        int num1 = 0;
        int num2 = 0;


        int a[200000];
        int b[200000];
        int c[200000];
        int d[200000];



        scanf("%d %d", &n, &m);

        for (int i=0; i<m; i++) {
                scanf("%d %d", &a[i], &b[i]);

                if (a[i] == 1) {
                        c[num1] = b[i];
                        num1++;
                }else if (b[i] == n) {
                        d[num2] = a[i];
                        num2++;
                }
        }

        if (num1 == 0 || num2 == 0) {
                printf("IMPOSSIBLE\n");
                return 0;
        }

        for (int i=0; i<num1; i++) {
                for (int j=num2-1; j>=0; j--) {
                        if (d[j] == c[i]) {
                                printf("POSSIBLE\n");
                                return 0;
                        }
                }
        }

        printf("IMPOSSIBLE\n");

        return 0;
}