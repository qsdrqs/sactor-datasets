#include <stdio.h>

int main(int argc, const char * argv[]) {
    int a,b,d,r;
    double f;
    scanf("%d %d",&a,&b);
    d = a/b;
    r = a%b;
    f = (double)a/b;
    printf("%d %d %lf\n",d,r,f);

    return 0;
}

