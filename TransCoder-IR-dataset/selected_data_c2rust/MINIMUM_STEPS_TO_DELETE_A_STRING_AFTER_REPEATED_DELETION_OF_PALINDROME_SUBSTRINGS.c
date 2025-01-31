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

int f_gold ( char str [] ) {
  int N = strlen(str);
  int dp [ N + 1 ] [ N + 1 ];
  for ( int i = 0;
  i <= N;
  i ++ ) for ( int j = 0;
  j <= N;
  j ++ ) dp [ i ] [ j ] = 0;
  for ( int len = 1;
  len <= N;
  len ++ ) {
    for ( int i = 0, j = len - 1;
    j < N;
    i ++, j ++ ) {
      if ( len == 1 ) dp [ i ] [ j ] = 1;
      else {
        dp [ i ] [ j ] = 1 + dp [ i + 1 ] [ j ];
        if ( str [ i ] == str [ i + 1 ] ) dp [ i ] [ j ] = min ( 1 + dp [ i + 2 ] [ j ], dp [ i ] [ j ] );
        for ( int K = i + 2;
        K <= j;
        K ++ ) if ( str [ i ] == str [ K ] ) dp [ i ] [ j ] = min ( dp [ i + 1 ] [ K - 1 ] + dp [ K + 1 ] [ j ], dp [ i ] [ j ] );
      }
    }
  }
  return dp [ 0 ] [ N - 1 ];
}


