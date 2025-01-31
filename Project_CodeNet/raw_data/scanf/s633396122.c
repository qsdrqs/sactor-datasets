#include <stdio.h>
#include <math.h>

void koch(double, double, double, double, int);

int main(){
    int n;
    double x1 = 0.0, x2 = 100.0;
    double y1 = 0.0, y2 = 0.0;

    scanf("%d", &n);
    printf("%f %f\n", x1, y1);
    koch(x1, y1, x2, y2, n);
    return 0;
}

void koch(double x1, double y1, double x2, double y2, int n){
    double ax, ay, bx, by, cx, cy;

    if(n != 0){

        ax = (x2 - x1) / 3 + x1;
        ay = (y2 - y1) / 3 + y1;
        bx = 2 * (x2 - x1) / 3 + x1;
        by = 2 * (y2 - y1) / 3 + y1;

        cx = ((bx - ax)* cos(M_PI/3) - (by - ay)* sin(M_PI/3)) + ax;      // ６０度回転
        cy = ((bx - ax)* sin(M_PI/3) + (by - ay)* cos(M_PI/3)) + ax;

        koch(x1, y1, ax, ay, n-1);
        koch(ax, ay, cx, cy, n-1);
        koch(cx, cy, bx, by, n-1);
        koch(bx, by, x2, x2, n-1);
    }
    else {
        printf("%f %f\n", x2, y2);

    }
}