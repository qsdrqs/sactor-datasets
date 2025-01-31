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
  int i;
  int ans = INT_MIN;
  int maxval = 1;
  int minval = 1;
  int prevMax;
  for ( i = 0;
  i < n;
  i ++ ) {
    if ( arr [ i ] > 0 ) {
      maxval = maxval * arr [ i ];
      minval = min ( 1, minval * arr [ i ] );
    }
    else if ( arr [ i ] == 0 ) {
      minval = 1;
      maxval = 0;
    }
    else if ( arr [ i ] < 0 ) {
      prevMax = maxval;
      maxval = minval * arr [ i ];
      minval = prevMax * arr [ i ];
    }
    ans = max ( ans, maxval );
    if ( maxval <= 0 ) {
      maxval = 1;
    }
  }
  return ans;
}


