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

int f_gold ( char a [], char b [] ) {
  int n = len(a), m = len(b);
  if ( m == 0 ) return 1;
  int dp [ m + 1 ] [ n + 1 ];
  memset ( dp, 0, sizeof ( dp ) );
  for ( int i = 0;
  i < m;
  i ++ ) {
    for ( int j = i;
    j < n;
    j ++ ) {
      if ( i == 0 ) {
        if ( j == 0 ) dp [ i ] [ j ] = ( a [ j ] == b [ i ] ) ? 1 : 0;
        else if ( a [ j ] == b [ i ] ) dp [ i ] [ j ] = dp [ i ] [ j - 1 ] + 1;
        else dp [ i ] [ j ] = dp [ i ] [ j - 1 ];
      }
      else {
        if ( a [ j ] == b [ i ] ) dp [ i ] [ j ] = dp [ i ] [ j - 1 ] + dp [ i - 1 ] [ j - 1 ];
        else dp [ i ] [ j ] = dp [ i ] [ j - 1 ];
      }
    }
  }
  return dp [ m - 1 ] [ n - 1 ];
}


int f_filled ( char a [], char b [] ) {
  int n = len(a), m = len(b);
  if ( m == 0 ) return 1;
  int dp [ m + 1 ] [ n + 1 ];
  memset ( dp, 0, sizeof ( dp ) );
  for ( int i = 0;
  i < m;
  i ++ ) {
    for ( int j = i;
    j < n;
    j ++ ) {
      if ( i == 0 ) {
        if ( j == 0 ) dp [ i ] [ j ] = ( a [ j ] == b [ i ] ) ? 1 : 0;
        else if ( a [ j ] == b [ i ] ) dp [ i ] [ j ] = dp [ i ] [ j - 1 ] + 1;
        else dp [ i ] [ j ] = dp [ i ] [ j - 1 ];
      }
      else {
        if ( a [ j ] == b [ i ] ) dp [ i ] [ j ] = dp [ i ] [ j - 1 ] + dp [ i - 1 ] [ j - 1 ];
        else dp [ i ] [ j ] = dp [ i ] [ j - 1 ];
      }
    }
  }
  return dp [ m - 1 ] [ n - 1 ];
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    char param0[][100] = {"abcccdf","aabba","aabsdfljk","IONiqV","9667771256770","10001011","fczbDtMDT","298746088","01100011000","Qk"};
    char param1[][100] = {"abccdf","ab","aa","XKbBiGZ","50915176","01","FbX","29888","0",""};
int i = argc > 1 ? atoi(argv[1]) : 0;
        if(f_filled(param0[i],param1[i]) == f_gold(param0[i],param1[i]))
        {
            return 0;
        }

        else {
            printf("Test failed for input: \n");
            printf("param0 (first 1 element): "); print_array(param0[i], 1);
            printf("param1 (first 1 element): "); print_array(param1[i], 1);
            printf("Expected: %d\n", f_gold(param0[i], param1[i]));
            printf("Got: %d\n", f_filled(param0[i], param1[i]));
            return -1;
        }
if (n_success != len(param0)) return -1;
    return 0;
}