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

int f_gold ( int N, int insert, int remove, int copy ) {
  if ( N == 0 ) return 0;
  if ( N == 1 ) return insert;
  int dp [ N + 1 ];
  memset ( dp, 0, sizeof ( dp ) );
  for ( int i = 1;
  i <= N;
  i ++ ) {
    if ( i % 2 == 0 ) dp [ i ] = min ( dp [ i - 1 ] + insert, dp [ i / 2 ] + copy );
    else dp [ i ] = min ( dp [ i - 1 ] + insert, dp [ ( i + 1 ) / 2 ] + copy + remove );
  }
  return dp [ N ];
}


int f_filled ( int N, int insert, int remove, int copy ) {
  if ( N == 0 ) return 0;
  if ( N == 1 ) return insert;
  int dp [ N + 1 ];
  memset ( dp, 0, sizeof ( dp ) );
  for ( int i = 1;
  i <= N;
  i ++ ) {
    if ( i % 2 == 0 ) dp [ i ] = min ( dp [ i - 1 ] + insert, dp [ i / 2 ] + copy );
    else dp [ i ] = min ( dp [ i - 1 ] + insert, dp [ ( i + 1 ) / 2 ] + copy + remove );
  }
  return dp [ N ];
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    int param0[] = {59,66,98,63,99,45,60,11,96,54};
    int param1[] = {75,68,55,4,37,28,53,96,95,6};
    int param2[] = {12,32,69,41,98,59,40,50,48,50};
    int param3[] = {45,41,5,12,55,7,52,50,84,82};
int i = argc > 1 ? atoi(argv[1]) : 0;
        if(f_filled(param0[i],param1[i],param2[i],param3[i]) == f_gold(param0[i],param1[i],param2[i],param3[i]))
        {
            return 0;
        }

        else {
            printf("Test failed for input: \n");
            printf("param0: %d\n", param0[i]);
            printf("param1: %d\n", param1[i]);
            printf("param2: %d\n", param2[i]);
            printf("param3: %d\n", param3[i]);
            printf("Expected: %d\n", f_gold(param0[i], param1[i], param2[i], param3[i]));
            printf("Got: %d\n", f_filled(param0[i], param1[i], param2[i], param3[i]));
            return -1;
        }
if (n_success != len(param0)) return -1;
    return 0;
}