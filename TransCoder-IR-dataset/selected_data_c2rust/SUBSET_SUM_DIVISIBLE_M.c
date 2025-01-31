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

bool f_gold ( int arr [ ], int n, int m ) {
  if ( n > m ) return true;
  bool DP [ m ];
  memset ( DP, false, m );
  for ( int i = 0;
  i < n;
  i ++ ) {
    if ( DP [ 0 ] ) return true;
    bool temp [ m ];
    memset ( temp, false, m );
    for ( int j = 0;
    j < m;
    j ++ ) {
      if ( DP [ j ] == true ) {
        if ( DP [ ( j + arr [ i ] ) % m ] == false ) temp [ ( j + arr [ i ] ) % m ] = true;
      }
    }
    for ( int j = 0;
    j < m;
    j ++ ) if ( temp [ j ] ) DP [ j ] = true;
    DP [ arr [ i ] % m ] = true;
  }
  return DP [ 0 ];
}


