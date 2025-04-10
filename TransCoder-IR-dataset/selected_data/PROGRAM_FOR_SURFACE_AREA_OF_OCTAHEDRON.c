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

double f_gold ( double side ) {
  return ( 2 * ( sqrt ( 3 ) ) * ( side * side ) );
}


double f_filled ( double side ) {
  return ( 2 * ( sqrt ( 3 ) ) * ( side * side ) );
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    double param0[] = {1449.255716877097,-8772.104874265995,2948.419328234334,-1184.220109553511,7422.825800698956,-5808.280006171851,829.8963781665169,-7368.438572511732,5572.033890611617,-3998.9441642787706};
int i = argc > 1 ? atoi(argv[1]) : 0;
        if(abs(1 - (0.0000001 + abs(f_gold(param0[i])) )/ (abs(f_filled(param0[i])) + 0.0000001)) < 0.001)
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