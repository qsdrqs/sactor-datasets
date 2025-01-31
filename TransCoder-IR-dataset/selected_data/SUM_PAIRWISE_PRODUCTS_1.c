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

long long int f_gold ( int n ) {
  long long int multiTerms = n * ( n + 1 ) / 2;
  long long int sum = multiTerms;
  for ( int i = 2;
  i <= n;
  i ++ ) {
    multiTerms = multiTerms - ( i - 1 );
    sum = sum + multiTerms * i;
  }
  return sum;
}


long long int f_filled ( int n ) {
  long long int multiTerms = n * ( n + 1 ) / 2;
  long long int sum = multiTerms;
  for ( int i = 2;
  i <= n;
  i ++ ) {
    multiTerms = multiTerms - ( i - 1 );
    sum = sum + multiTerms * i;
  }
  return sum;
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    int param0[] = {41,50,67,18,60,6,27,46,50,20};
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