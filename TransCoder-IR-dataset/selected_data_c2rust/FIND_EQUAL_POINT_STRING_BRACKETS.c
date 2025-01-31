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
  int len = strlen(str);
  int open [ len + 1 ], close [ len + 1 ];
  int index = - 1;
  memset ( open, 0, sizeof ( open ) );
  memset ( close, 0, sizeof ( close ) );
  open [ 0 ] = 0;
  close [ len ] = 0;
  if ( str [ 0 ] == '(' ) open [ 1 ] = 1;
  if ( str [ len - 1 ] == ')' ) close [ len - 1 ] = 1;
  for ( int i = 1;
  i < len;
  i ++ ) {
    if ( str [ i ] == '(' ) open [ i + 1 ] = open [ i ] + 1;
    else open [ i + 1 ] = open [ i ];
  }
  for ( int i = len - 2;
  i >= 0;
  i -- ) {
    if ( str [ i ] == ')' ) close [ i ] = close [ i + 1 ] + 1;
    else close [ i ] = close [ i + 1 ];
  }
  if ( open [ len ] == 0 ) return len;
  if ( close [ 0 ] == 0 ) return 0;
  for ( int i = 0;
  i <= len;
  i ++ ) if ( open [ i ] == close [ i ] ) index = i;
  return index;
}


