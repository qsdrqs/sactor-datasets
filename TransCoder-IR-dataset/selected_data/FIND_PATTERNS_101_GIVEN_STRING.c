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
  char last = str [ 0 ];
  int i = 1, counter = 0;
  while ( i < len(str) ) {
    if ( str [ i ] == '0' && last == '1' ) {
      while ( str [ i ] == '0' ) i ++;
      if ( str [ i ] == '1' ) counter ++;
    }
    last = str [ i ];
    i ++;
  }
  return counter;
}


int f_filled ( char str [] ) {
  char last = str [ 0 ];
  int i = 1, counter = 0;
  while ( i < len(str) ) {
    if ( str [ i ] == '0' && last == '1' ) {
      while ( str [ i ] == '0' ) i ++;
      if ( str [ i ] == '1' ) counter ++;
    }
    last = str [ i ];
    i ++;
  }
  return counter;
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    char param0[][100] = {"fkyso nGZSLfhj","3841","0100001110111","zXZkptcbnQot","4364264685264","10","wDgox","1215572","1","bftZvRTamdUvL"};
int i = argc > 1 ? atoi(argv[1]) : 0;
        if(f_filled(param0[i]) == f_gold(param0[i]))
        {
            return 0;
        }

        else {
            printf("Test failed for input: \n");
            printf("param0 (first 1 element): "); print_array(param0[i], 1);
            printf("Expected: %d\n", f_gold(param0[i]));
            printf("Got: %d\n", f_filled(param0[i]));
            return -1;
        }
if (n_success != len(param0)) return -1;
    return 0;
}