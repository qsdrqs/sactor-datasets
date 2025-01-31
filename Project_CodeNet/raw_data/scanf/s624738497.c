#include <stdio.h>
#include <string.h>
#include<math.h>
#include <stdlib.h>
int main()
{
        double h, n, w, N;
        a:while (scanf("%lf", &N) != EOF)
        {
                for (h = 1; h <= 3500;h++)
                {
                        for (n = 1; n <= 3500; n++)
                        {
                                w = 1.0 / (4.0 / N - 1.0 / n - 1.0 / h);
                                if (w >= 0.0 && w <= 3500.0 && w == (int)w)
                                {
                                        printf("%.0lf %.0lf %.0lf\n",h,n,w);
                                        goto a;
                                }
                        }
                }
        }
}