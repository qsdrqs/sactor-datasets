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

int f_gold ( char S [], char T [] ) {
  int m = strlen(T), n = strlen(S);
  if ( m > n ) return 0;
  int mat [ m + 1 ] [ n + 1 ];
  for ( int i = 1;
  i <= m;
  i ++ ) mat [ i ] [ 0 ] = 0;
  for ( int j = 0;
  j <= n;
  j ++ ) mat [ 0 ] [ j ] = 1;
  for ( int i = 1;
  i <= m;
  i ++ ) {
    for ( int j = 1;
    j <= n;
    j ++ ) {
      if ( T [ i - 1 ] != S [ j - 1 ] ) mat [ i ] [ j ] = mat [ i ] [ j - 1 ];
      else mat [ i ] [ j ] = mat [ i ] [ j - 1 ] + mat [ i - 1 ] [ j - 1 ];
    }
  }
  return mat [ m ] [ n ];
}


