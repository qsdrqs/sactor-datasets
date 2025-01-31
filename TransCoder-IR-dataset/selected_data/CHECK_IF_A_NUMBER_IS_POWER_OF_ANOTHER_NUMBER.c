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

bool f_gold ( int x, long int y ) {
  if ( x == 1 ) return ( y == 1 );
  long int pow = 1;
  while ( pow < y ) pow *= x;
  return ( pow == y );
}


bool f_filled ( int x, long int y ) {
  if ( x == 1 ) return ( y == 1 );
  long int pow = 1;
  while ( pow < y ) pow *= x;
  return ( pow == y );
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    int param0[] = {57,3,10,10,6,2,1,20,96,25};
    int param1[] = {1,9,101,10000,46656,2048,40,79,98,5};
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