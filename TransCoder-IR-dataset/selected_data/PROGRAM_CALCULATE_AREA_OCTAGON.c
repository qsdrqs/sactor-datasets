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
  return ( float ) ( 2 * ( 1 + sqrt ( 2 ) ) * side * side );
}


double f_filled ( double side ) {
  return ( float ) ( 2 * ( 1 + sqrt ( 2 ) ) * side * side );
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    double param0[] = {5859.798616323926,-6381.210375893524,2442.246292006922,-9624.81536339737,8679.436805247444,-2682.3245401089525,7216.9161613024435,-5881.789859815442,2497.776395789202,-9598.912195459263};
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