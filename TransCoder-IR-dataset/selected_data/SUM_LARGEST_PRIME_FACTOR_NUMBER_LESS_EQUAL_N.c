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

int f_gold ( int n ) {
  int prime [ n + 1 ], sum = 0;
  memset ( prime, 0, sizeof ( prime ) );
  int max = n / 2;
  for ( int p = 2;
  p <= max;
  p ++ ) {
    if ( prime [ p ] == 0 ) {
      for ( int i = p * 2;
      i <= n;
      i += p ) prime [ i ] = p;
    }
  }
  for ( int p = 2;
  p <= n;
  p ++ ) {
    if ( prime [ p ] ) sum += prime [ p ];
    else sum += p;
  }
  return sum;
}


int f_filled ( int n ) {
  int prime [ n + 1 ], sum = 0;
  memset ( prime, 0, sizeof ( prime ) );
  int max = n / 2;
  for ( int p = 2;
  p <= max;
  p ++ ) {
    if ( prime [ p ] == 0 ) {
      for ( int i = p * 2;
      i <= n;
      i += p ) prime [ i ] = p;
    }
  }
  for ( int p = 2;
  p <= n;
  p ++ ) {
    if ( prime [ p ] ) sum += prime [ p ];
    else sum += p;
  }
  return sum;
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    int param0[] = {6,35,87,91,63,11,66,17,92,81};
int i = argc > 1 ? atoi(argv[1]) : 0;
        if(f_filled(param0[i]) == f_gold(param0[i]))
        {
            return 0;
        }

        else {
            printf("Test failed for input: \n");
            printf("param0: %d\n", param0[i]);
            printf("Expected: %d\n", f_gold(param0[i]));
            printf("Got: %d\n", f_filled(param0[i]));
            return -1;
        }
if (n_success != len(param0)) return -1;
    return 0;
}