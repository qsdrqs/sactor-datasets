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

int f_gold ( long long int A, long long int B ) {
  int variable = 1;
  if ( A == B ) return 1;
  else if ( ( B - A ) >= 5 ) return 0;
  else {
    for ( long long int i = A + 1;
    i <= B;
    i ++ ) variable = ( variable * ( i % 10 ) ) % 10;
    return variable % 10;
  }
}


int f_filled ( long long int A, long long int B ) {
  int variable = 1;
  if ( A == B ) return 1;
  else if ( ( B - A ) >= 5 ) return 0;
  else {
    for ( long long int i = A + 1;
    i <= B;
    i ++ ) variable = ( variable * ( i % 10 ) ) % 10;
    return variable % 10;
  }
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    long param0[] = {79,61,39,39,61,86,7,86,86,11};
    long param1[] = {84,29,77,65,78,73,92,50,63,2};
int i = argc > 1 ? atoi(argv[1]) : 0;
        if(f_filled(param0[i],param1[i]) == f_gold(param0[i],param1[i]))
        {
            return 0;
        }

        else {
            printf("Test failed for input: \n");
            printf("param0: %d\n", param0[i]);
            printf("param1: %d\n", param1[i]);
            printf("Expected: %d\n", f_gold(param0[i], param1[i]));
            printf("Got: %d\n", f_filled(param0[i], param1[i]));
            return -1;
        }
if (n_success != len(param0)) return -1;
    return 0;
}