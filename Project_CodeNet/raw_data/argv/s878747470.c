#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
        int a = atoi(argv[1]);
        int b = atoi(argv[2]);
        int c = atoi(argv[3]);
        int d = atoi(argv[4]);
        int e = atoi(argv[5]);
        int f = atoi(argv[6]);

        int tr = a*e-b*d;
        double x = (int)(1000*(e*c - b*f)/tr)/1000.0;
        double y = (int)(1000*(a*f - d*c)/tr)/1000.0;

        printf("%.3f %.3f\n",x,y);

        return 0;
}