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

bool f_gold ( char str1 [], char str2 [], int k ) {
  if ( ( strlen(str1) + strlen(str2) ) < k ) return true;
  int commonLength = 0;
  for ( int i = 0;
  i < min ( strlen(str1), strlen(str2) );
  i ++ ) {
    if ( str1 [ i ] == str2 [ i ] ) commonLength ++;
    else break;
  }
  if ( ( k - strlen(str1) - strlen(str2) + 2 * commonLength ) % 2 == 0 ) return true;
  return false;
}


