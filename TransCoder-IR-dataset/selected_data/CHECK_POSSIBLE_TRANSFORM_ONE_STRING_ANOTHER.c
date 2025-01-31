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

bool f_gold ( char s1 [], char s2 [] ) {
  int n = strlen(s1);
  int m = strlen(s2);
  bool dp [ n + 1 ] [ m + 1 ];
  for ( int i = 0;
  i <= n;
  i ++ ) {
    for ( int j = 0;
    j <= m;
    j ++ ) {
      dp [ i ] [ j ] = false;
    }
  }
  dp [ 0 ] [ 0 ] = true;
  for ( int i = 0;
  i < strlen(s1);
  i ++ ) {
    for ( int j = 0;
    j <= strlen(s2);
    j ++ ) {
      if ( dp [ i ] [ j ] ) {
        if ( j < strlen(s2) && ( toupper ( s1 [ i ] ) == s2 [ j ] ) ) dp [ i + 1 ] [ j + 1 ] = true;
        if ( ! isupper ( s1 [ i ] ) ) dp [ i + 1 ] [ j ] = true;
      }
    }
  }
  return ( dp [ n ] [ m ] );
}


bool f_filled ( char s1 [], char s2 [] ) {
  int n = strlen(s1);
  int m = strlen(s2);
  bool dp [ n + 1 ] [ m + 1 ];
  for ( int i = 0;
  i <= n;
  i ++ ) {
    for ( int j = 0;
    j <= m;
    j ++ ) {
      dp [ i ] [ j ] = false;
    }
  }
  dp [ 0 ] [ 0 ] = true;
  for ( int i = 0;
  i < strlen(s1);
  i ++ ) {
    for ( int j = 0;
    j <= strlen(s2);
    j ++ ) {
      if ( dp [ i ] [ j ] ) {
        if ( j < strlen(s2) && ( toupper ( s1 [ i ] ) == s2 [ j ] ) ) dp [ i + 1 ] [ j + 1 ] = true;
        if ( ! isupper ( s1 [ i ] ) ) dp [ i + 1 ] [ j ] = true;
      }
    }
  }
  return ( dp [ n ] [ m ] );
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    char param0[][100] = {"daBcd","417514","010000","ZcKYguiMrdyn","argaju","1110101101","ySOCoSaygi","204","10011100000010","nMAioozPmY"};
    char param1[][100] = {"ABC","9","1111011010","iz","RAJ","110101001","aRhxkYqh","6986871066","0","WZFdDKw"};
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