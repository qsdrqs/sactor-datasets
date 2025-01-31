#include <stdio.h>
#include <stdlib.h>

struct d {
    int n;
    int v;
};

int cmpfunc( const void *a, const void *b )
{
    return( ((struct d *) b)->v - ((struct d *) a)->v );
}

int main( int argc, char *argv[] )
{
    int n;
//    int dp[10000][2];
    struct d a[10000];
    long long l, r;
    long long dpl, dplx, dply;
    long long dpr, dprx, dpry;

    scanf( "%d", &n );
    for( int i=0; i<n; i++ ) {
        a[i].n = i+1;
        scanf( "%d", &a[i].v );
    }

    qsort( a, n, sizeof(struct d), cmpfunc );

    for( int i=0; i<n; i++ )
        printf( "%2d : %d\n", a[i].n, a[i].v );

    dpl = (long long) a[0].v * (a[0].n - 1);
    dpr = (long long) a[0].v * (n - a[0].n);
    dplx = 1;
    dply = 0;
    dprx = 0;
    dpry = 1;

    for( int i=1; i<n; i++ ) {

//    printf( "%d %d %d : %d %d %d\n", dpl, dplx, dply, dpr, dprx, dpry );

        l = dpl + a[i].v * abs(dplx+1 - a[i].n);
        r = dpl + a[i].v * abs(n-dply - a[i].n);

        if( l > r ) {
            dpl = l;
            dplx ++;
        } else {
            dpl = r;
            dply ++;
        }

        l = dpr + a[i].v * abs(dprx+1 - a[i].n);
        r = dpr + a[i].v * abs(n-dpry - a[i].n);

        if( l > r ) {
            dpr = l;
            dprx ++;
        } else {
            dpr = r;
            dpry ++;
        }
    }

    if( dpl > dpr ) printf( "%lld\n", dpl );
    else            printf( "%lld\n", dpr );
}
