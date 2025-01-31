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

int f_gold ( char str [ ], int n ) {
  int dp [ n ] [ n ];
  memset ( dp, 0, sizeof ( dp ) );
  bool P [ n ] [ n ];
  memset ( P, false, sizeof ( P ) );
  for ( int i = 0;
  i < n;
  i ++ ) P [ i ] [ i ] = true;
  for ( int i = 0;
  i < n - 1;
  i ++ ) {
    if ( str [ i ] == str [ i + 1 ] ) {
      P [ i ] [ i + 1 ] = true;
      dp [ i ] [ i + 1 ] = 1;
    }
  }
  for ( int gap = 2;
  gap < n;
  gap ++ ) {
    for ( int i = 0;
    i < n - gap;
    i ++ ) {
      int j = gap + i;
      if ( str [ i ] == str [ j ] && P [ i + 1 ] [ j - 1 ] ) P [ i ] [ j ] = true;
      if ( P [ i ] [ j ] == true ) dp [ i ] [ j ] = dp [ i ] [ j - 1 ] + dp [ i + 1 ] [ j ] + 1 - dp [ i + 1 ] [ j - 1 ];
      else dp [ i ] [ j ] = dp [ i ] [ j - 1 ] + dp [ i + 1 ] [ j ] - dp [ i + 1 ] [ j - 1 ];
    }
  }
  return dp [ 0 ] [ n - 1 ];
}


int f_filled ( char str [ ], int n ) {
  int dp [ n ] [ n ];
  memset ( dp, 0, sizeof ( dp ) );
  bool P [ n ] [ n ];
  memset ( P, false, sizeof ( P ) );
  for ( int i = 0;
  i < n;
  i ++ ) P [ i ] [ i ] = true;
  for ( int i = 0;
  i < n - 1;
  i ++ ) {
    if ( str [ i ] == str [ i + 1 ] ) {
      P [ i ] [ i + 1 ] = true;
      dp [ i ] [ i + 1 ] = 1;
    }
  }
  for ( int gap = 2;
  gap < n;
  gap ++ ) {
    for ( int i = 0;
    i < n - gap;
    i ++ ) {
      int j = gap + i;
      if ( str [ i ] == str [ j ] && P [ i + 1 ] [ j - 1 ] ) P [ i ] [ j ] = true;
      if ( P [ i ] [ j ] == true ) dp [ i ] [ j ] = dp [ i ] [ j - 1 ] + dp [ i + 1 ] [ j ] + 1 - dp [ i + 1 ] [ j - 1 ];
      else dp [ i ] [ j ] = dp [ i ] [ j - 1 ] + dp [ i + 1 ] [ j ] - dp [ i + 1 ] [ j - 1 ];
    }
  }
  return dp [ 0 ] [ n - 1 ];
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    char param0_0[] = {'E','E','J','P','T','U','X','Y','Z','e','f','h','l','m','n','o','z'};
char param0_1[] = {'8','7','3','4','9','5','3','1','4','0','6','8','2','5','8','3','5','2','8','6','6','3','5','7','5','5','3','7'};
char param0_2[] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'};
char param0_3[] = {'f','E','e','z','B','o','i','v','K','u','P','C','z','f','k','J','t','R','t','A','f','G','D','X','H','e','p','l','l','k','Z','Y','u','g','H','C','f','J','H','W'};
char param0_4[] = {'0','0','0','1','1','1','1','1','1','2','2','2','3','3','3','3','3','4','4','4','4','4','4','5','5','5','5','6','6','7','7','9','9','9','9','9','9'};
char param0_5[] = {'1','0','1','1','0','0','1','1','1','0','1','0','1','1','0','1','0','1','1','1','1','1','0','1','1','0','1','0','1','1','0','0','1','0','1','0','0','0','0','0','1','1','0','1','0','1'};
char param0_6[] = {'C','C','D','F','L','M','P','X','a','f','i','j','w'};
char param0_7[] = {'7','9','0','2','8','0','7','5','9','4','5','4','8','1','9','5','3','2','4','1','2'};
char param0_8[] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'};
char param0_9[] = {'m','X','N','M'};
char *param0[10] = {param0_0,param0_1,param0_2,param0_3,param0_4,param0_5,param0_6,param0_7,param0_8,param0_9};
    int param1[] = {11,27,23,27,35,43,9,16,32,3};
int i = argc > 1 ? atoi(argv[1]) : 0;
        if(f_filled(param0[i],param1[i]) == f_gold(param0[i],param1[i]))
        {
            return 0;
        }

        else {
            printf("Test failed for input: \n");
            printf("param0 (first 1 element): "); print_array(param0[i], 1);
            printf("param1: %d\n", param1[i]);
            printf("Expected: %d\n", f_gold(param0[i], param1[i]));
            printf("Got: %d\n", f_filled(param0[i], param1[i]));
            return -1;
        }
if (n_success != len(param0)) return -1;
    return 0;
}