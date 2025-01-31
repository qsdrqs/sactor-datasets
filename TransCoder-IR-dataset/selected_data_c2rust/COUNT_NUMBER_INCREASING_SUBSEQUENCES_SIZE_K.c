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

int f_gold ( int arr [ ], int n, int k ) {
  int dp [ k ] [ n ], sum = 0;
  memset ( dp, 0, sizeof ( dp ) );
  for ( int i = 0;
  i < n;
  i ++ ) dp [ 0 ] [ i ] = 1;
  for ( int l = 1;
  l < k;
  l ++ ) {
    for ( int i = l;
    i < n;
    i ++ ) {
      dp [ l ] [ i ] = 0;
      for ( int j = l - 1;
      j < i;
      j ++ ) {
        if ( arr [ j ] < arr [ i ] ) dp [ l ] [ i ] += dp [ l - 1 ] [ j ];
      }
    }
  }
  for ( int i = k - 1;
  i < n;
  i ++ ) sum += dp [ k - 1 ] [ i ];
  return sum;
}


