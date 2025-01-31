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

int f_gold ( int arr [ ], int n ) {
  if ( n == 1 ) return arr [ 0 ];
  int dec [ n ];
  memset ( dec, 0, sizeof ( dec ) );
  int inc [ n ];
  memset ( inc, 0, sizeof ( inc ) );
  dec [ 0 ] = inc [ 0 ] = arr [ 0 ];
  int flag = 0;
  for ( int i = 1;
  i < n;
  i ++ ) {
    for ( int j = 0;
    j < i;
    j ++ ) {
      if ( arr [ j ] > arr [ i ] ) {
        dec [ i ] = max ( dec [ i ], inc [ j ] + arr [ i ] );
        flag = 1;
      }
      else if ( arr [ j ] < arr [ i ] && flag == 1 ) inc [ i ] = max ( inc [ i ], dec [ j ] + arr [ i ] );
    }
  }
  int result = INT_MIN;
  for ( int i = 0;
  i < n;
  i ++ ) {
    if ( result < inc [ i ] ) result = inc [ i ];
    if ( result < dec [ i ] ) result = dec [ i ];
  }
  return result;
}


