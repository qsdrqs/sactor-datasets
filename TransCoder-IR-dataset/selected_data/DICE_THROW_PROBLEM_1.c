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

long f_gold ( int f, int d, int s ) {
  long mem [ d + 1 ] [ s + 1 ];
  memset ( mem, 0, sizeof mem );
  mem [ 0 ] [ 0 ] = 1;
  for ( int i = 1;
  i <= d;
  i ++ ) {
    for ( int j = i;
    j <= s;
    j ++ ) {
      mem [ i ] [ j ] = mem [ i ] [ j - 1 ] + mem [ i - 1 ] [ j - 1 ];
      if ( j - f - 1 >= 0 ) mem [ i ] [ j ] -= mem [ i - 1 ] [ j - f - 1 ];
    }
  }
  return mem [ d ] [ s ];
}


long f_filled ( int f, int d, int s ) {
  long mem [ d + 1 ] [ s + 1 ];
  memset ( mem, 0, sizeof mem );
  mem [ 0 ] [ 0 ] = 1;
  for ( int i = 1;
  i <= d;
  i ++ ) {
    for ( int j = i;
    j <= s;
    j ++ ) {
      mem [ i ] [ j ] = mem [ i ] [ j - 1 ] + mem [ i - 1 ] [ j - 1 ];
      if ( j - f - 1 >= 0 ) mem [ i ] [ j ] -= mem [ i - 1 ] [ j - f - 1 ];
    }
  }
  return mem [ d ] [ s ];
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    int param0[] = {57,58,38,5,91,76,38,97,97,99};
    int param1[] = {5,45,89,39,90,56,43,26,90,2};
    int param2[] = {33,4,9,30,47,46,84,52,90,26};
int i = argc > 1 ? atoi(argv[1]) : 0;
        if(f_filled(param0[i],param1[i],param2[i]) == f_gold(param0[i],param1[i],param2[i]))
        {
            return 0;
        }

        else {
            printf("Test failed for input: \n");
            printf("param0: %d\n", param0[i]);
            printf("param1: %d\n", param1[i]);
            printf("param2: %d\n", param2[i]);
            printf("Expected: %d\n", f_gold(param0[i], param1[i], param2[i]));
            printf("Got: %d\n", f_filled(param0[i], param1[i], param2[i]));
            return -1;
        }
if (n_success != len(param0)) return -1;
    return 0;
}