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

long long int f_gold ( int n ) {
  long long int dp [ 10 ] [ n + 1 ];
  memset ( dp, 0, sizeof dp );
  for ( int i = 0;
  i < 10;
  i ++ ) dp [ i ] [ 1 ] = 1;
  for ( int digit = 0;
  digit <= 9;
  digit ++ ) {
    for ( int len = 2;
    len <= n;
    len ++ ) {
      for ( int x = 0;
      x <= digit;
      x ++ ) dp [ digit ] [ len ] += dp [ x ] [ len - 1 ];
    }
  }
  long long int count = 0;
  for ( int i = 0;
  i < 10;
  i ++ ) count += dp [ i ] [ n ];
  return count;
}


long long int f_filled ( int n ) {
  long long int dp [ 10 ] [ n + 1 ];
  memset ( dp, 0, sizeof dp );
  for ( int i = 0;
  i < 10;
  i ++ ) dp [ i ] [ 1 ] = 1;
  for ( int digit = 0;
  digit <= 9;
  digit ++ ) {
    for ( int len = 2;
    len <= n;
    len ++ ) {
      for ( int x = 0;
      x <= digit;
      x ++ ) dp [ digit ] [ len ] += dp [ x ] [ len - 1 ];
    }
  }
  long long int count = 0;
  for ( int i = 0;
  i < 10;
  i ++ ) count += dp [ i ] [ n ];
  return count;
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    int param0[] = {21,40,83,93,43,98,35,86,76,88};
int i = argc > 1 ? atoi(argv[1]) : 0;
        if(f_filled(param0[i]) == f_gold(param0[i]))
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