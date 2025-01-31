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

int f_gold ( int n, int r, int p ) {
  int C [ r + 1 ];
  memset ( C, 0, sizeof ( C ) );
  C [ 0 ] = 1;
  for ( int i = 1;
  i <= n;
  i ++ ) {
    for ( int j = min ( i, r );
    j > 0;
    j -- ) C [ j ] = ( C [ j ] + C [ j - 1 ] ) % p;
  }
  return C [ r ];
}


int f_filled ( int n, int r, int p ) {
  int C [ r + 1 ];
  memset ( C, 0, sizeof ( C ) );
  C [ 0 ] = 1;
  for ( int i = 1;
  i <= n;
  i ++ ) {
    for ( int j = min ( i, r );
    j > 0;
    j -- ) C [ j ] = ( C [ j ] + C [ j - 1 ] ) % p;
  }
  return C [ r ];
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    int param0[] = {82,45,44,88,90,98,80,60,52,71};
    int param1[] = {5,24,68,24,75,55,54,75,73,26};
    int param2[] = {94,95,61,43,57,43,88,65,86,45};
int i = argc > 1 ? atoi(argv[1]) : 0;
        if(f_filled(param0[i],param1[i],param2[i]) == f_gold(param0[i],param1[i],param2[i]))
        {
            return 0;
        }

        else {
            printf("Test failed for input: \n");
            printf("param0: %d\n", param0[i]);
            printf("param1: %d\n", param1[i]);
            printf("param2: %d\n", param2[i]);
            printf("Expected: %d\n", f_gold(param0[i], param1[i], param2[i]));
            printf("Got: %d\n", f_filled(param0[i], param1[i], param2[i]));
            return -1;
        }
if (n_success != len(param0)) return -1;
    return 0;
}