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

int f_gold ( int n, int a, int b, int c ) {
  int dp [ n + 1 ];
  memset ( dp, - 1, sizeof ( dp ) );
  dp [ 0 ] = 0;
  for ( int i = 0;
  i < n;
  i ++ ) {
    if ( dp [ i ] != - 1 ) {
      if ( i + a <= n ) dp [ i + a ] = max ( dp [ i ] + 1, dp [ i + a ] );
      if ( i + b <= n ) dp [ i + b ] = max ( dp [ i ] + 1, dp [ i + b ] );
      if ( i + c <= n ) dp [ i + c ] = max ( dp [ i ] + 1, dp [ i + c ] );
    }
  }
  return dp [ n ];
}


int f_filled ( int n, int a, int b, int c ) {
  int dp [ n + 1 ];
  memset ( dp, - 1, sizeof ( dp ) );
  dp [ 0 ] = 0;
  for ( int i = 0;
  i < n;
  i ++ ) {
    if ( dp [ i ] != - 1 ) {
      if ( i + a <= n ) dp [ i + a ] = max ( dp [ i ] + 1, dp [ i + a ] );
      if ( i + b <= n ) dp [ i + b ] = max ( dp [ i ] + 1, dp [ i + b ] );
      if ( i + c <= n ) dp [ i + c ] = max ( dp [ i ] + 1, dp [ i + c ] );
    }
  }
  return dp [ n ];
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    int param0[] = {23,62,32,82,94,44,4,53,9,23};
    int param1[] = {16,76,46,48,99,21,57,23,55,15};
    int param2[] = {23,81,1,72,62,46,2,80,26,73};
    int param3[] = {18,97,78,58,38,60,77,5,85,42};
int i = argc > 1 ? atoi(argv[1]) : 0;
        if(f_filled(param0[i],param1[i],param2[i],param3[i]) == f_gold(param0[i],param1[i],param2[i],param3[i]))
        {
            return 0;
        }

        else {
            printf("Test failed for input: \n");
            printf("param0: %d\n", param0[i]);
            printf("param1: %d\n", param1[i]);
            printf("param2: %d\n", param2[i]);
            printf("param3: %d\n", param3[i]);
            printf("Expected: %d\n", f_gold(param0[i], param1[i], param2[i], param3[i]));
            printf("Got: %d\n", f_filled(param0[i], param1[i], param2[i], param3[i]));
            return -1;
        }
if (n_success != len(param0)) return -1;
    return 0;
}