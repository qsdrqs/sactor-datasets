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

bool f_gold ( int degree [ ], int n ) {
  int deg_sum = 0;
  for ( int i = 0;
  i < n;
  i ++ ) deg_sum += degree [ i ];
  return ( 2 * ( n - 1 ) == deg_sum );
}


bool f_filled ( int degree [ ], int n ) {
  int deg_sum = 0;
  for ( int i = 0;
  i < n;
  i ++ ) deg_sum += degree [ i ];
  return ( 2 * ( n - 1 ) == deg_sum );
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    int param0_0[] = {2};
int param0_1[] = {1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,1,1,0,1,1,0,0,0,1,0,1,1,1,1,1,1,0,1,1,1,0,1,0,0};
int param0_2[] = {1,6,10,13,15,17,18,23,26,28,30,32,32,33,36,39,39,41,43,50,50,51,53,54,59,59,63,63,63,66,66,71,71,74,78,89,89,93};
int param0_3[] = {66,-96,-14,74,-20};
int param0_4[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int param0_5[] = {97,73,87,45,64,30,53,50,62,42,28,58,31,90};
int *param0[6] = {param0_0,param0_1,param0_2,param0_3,param0_4,param0_5};
    int param1[] = {5,5,5,6,3,19,30,4,31,10};
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