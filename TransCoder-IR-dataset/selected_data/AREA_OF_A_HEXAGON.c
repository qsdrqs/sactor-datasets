#include <string.h>
#include <ctype.h>
// Copyright (c) 2019-present, Facebook, Inc.
// All rights reserved.
//
// This source code is licensed under the license found in the
// LICENSE file in the root directory of this source tree.
//


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int min(int x, int y) { return (x < y)? x: y; }
int max(int x, int y) { return (x > y)? x: y; }
int cmpfunc (const void * a, const void * b) {return ( *(int*)a - *(int*)b );}
#define len(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))
#define print_array(arr, len) for (int i = 0; i < len; i++) printf("%d ", arr[i]); printf("\n")
void sort (int arr [ ], int n) {qsort (arr, n, sizeof(int), cmpfunc);}

double f_gold ( double s ) {
  return ( ( 3 * sqrt ( 3 ) * ( s * s ) ) / 2 );
}


double f_filled ( double s ) {
  return ( ( 3 * sqrt ( 3 ) * ( s * s ) ) / 2 );
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    double param0[] = {1772.6589509256596,-599.737107809315,1074.1765931782,-1182.4087746714795,8083.035797247716,-6126.414356565494,5370.057504189614,-6947.020794285176,2110.5107873533325,-6458.751326919488};
int i = argc > 1 ? atoi(argv[1]) : 0;
        if(abs(1 - (0.0000001 + abs(f_gold(param0[i])) )/ (abs(f_filled(param0[i])) + 0.0000001)) < 0.001)
        {
            return 0;
        }

        else {
            printf("Test failed for input: \n");
            printf("param0: %d\n", param0[i]);
            printf("Expected: %d\n", f_gold(param0[i]));
            printf("Got: %d\n", f_filled(param0[i]));
            return -1;
        }
if (n_success != len(param0)) return -1;
    return 0;
}