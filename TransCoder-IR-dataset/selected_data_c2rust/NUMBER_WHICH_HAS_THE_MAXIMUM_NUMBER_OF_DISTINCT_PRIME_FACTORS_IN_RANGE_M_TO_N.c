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

int f_gold ( int m, int n ) {
  long long factorCount [ n + 1 ];
  bool prime [ n + 1 ];
  for ( int i = 0;
  i <= n;
  i ++ ) {
    factorCount [ i ] = 0;
    prime [ i ] = true;
  }
  for ( int i = 2;
  i <= n;
  i ++ ) {
    if ( prime [ i ] == true ) {
      factorCount [ i ] = 1;
      for ( int j = i * 2;
      j <= n;
      j += i ) {
        factorCount [ j ] ++;
        prime [ j ] = false;
      }
    }
  }
  int max = factorCount [ m ];
  int num = m;
  for ( int i = m;
  i <= n;
  i ++ ) {
    if ( factorCount [ i ] > max ) {
      max = factorCount [ i ];
      num = i;
    }
  }
  return num;
}


