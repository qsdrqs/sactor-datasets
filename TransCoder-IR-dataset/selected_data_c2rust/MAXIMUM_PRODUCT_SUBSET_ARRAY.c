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

int f_gold ( int a [ ], int n ) {
  if ( n == 1 ) return a [ 0 ];
  int max_neg = INT_MIN;
  int count_neg = 0, count_zero = 0;
  int prod = 1;
  for ( int i = 0;
  i < n;
  i ++ ) {
    if ( a [ i ] == 0 ) {
      count_zero ++;
      continue;
    }
    if ( a [ i ] < 0 ) {
      count_neg ++;
      max_neg = max ( max_neg, a [ i ] );
    }
    prod = prod * a [ i ];
  }
  if ( count_zero == n ) return 0;
  if ( count_neg & 1 ) {
    if ( count_neg == 1 && count_zero > 0 && count_zero + count_neg == n ) return 0;
    prod = prod / max_neg;
  }
  return prod;
}


