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

int f_gold ( int W, int n, int val [ ], int wt [ ] ) {
  int dp [ W + 1 ];
  memset ( dp, 0, sizeof dp );
  int ans = 0;
  for ( int i = 0;
  i <= W;
  i ++ ) for ( int j = 0;
  j < n;
  j ++ ) if ( wt [ j ] <= i ) dp [ i ] = max ( dp [ i ], dp [ i - wt [ j ] ] + val [ j ] );
  return dp [ W ];
}


