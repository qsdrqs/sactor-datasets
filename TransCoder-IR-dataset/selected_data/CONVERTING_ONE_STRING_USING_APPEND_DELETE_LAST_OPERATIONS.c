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

bool f_gold ( char str1 [], char str2 [], int k ) {
  if ( ( strlen(str1) + strlen(str2) ) < k ) return true;
  int commonLength = 0;
  for ( int i = 0;
  i < min ( strlen(str1), strlen(str2) );
  i ++ ) {
    if ( str1 [ i ] == str2 [ i ] ) commonLength ++;
    else break;
  }
  if ( ( k - strlen(str1) - strlen(str2) + 2 * commonLength ) % 2 == 0 ) return true;
  return false;
}


bool f_filled ( char str1 [], char str2 [], int k ) {
  if ( ( strlen(str1) + strlen(str2) ) < k ) return true;
  int commonLength = 0;
  for ( int i = 0;
  i < min ( strlen(str1), strlen(str2) );
  i ++ ) {
    if ( str1 [ i ] == str2 [ i ] ) commonLength ++;
    else break;
  }
  if ( ( k - strlen(str1) - strlen(str2) + 2 * commonLength ) % 2 == 0 ) return true;
  return false;
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    char param0[][100] = {"ZNHGro","382880806774","0","lxHTRFCTSQ","6399914758","01100011100000","WkGqlob","46974006151","1001001","IJQ"};
    char param1[][100] = {"jAdbtDUYQu","65565","00100010100","sViXYE","780990121","0100","NpQVdXzEtUZy","74438","1000010","nFOHAeYEAp"};
    int param2[] = {3,10,2,89,9,0,6,11,15,42};
int i = argc > 1 ? atoi(argv[1]) : 0;
        if(f_filled(param0[i],param1[i],param2[i]) == f_gold(param0[i],param1[i],param2[i]))
        {
            return 0;
        }

        else {
            printf("Test failed for input: \n");
            printf("param0 (first 1 element): "); print_array(param0[i], 1);
            printf("param1 (first 1 element): "); print_array(param1[i], 1);
            printf("param2: %d\n", param2[i]);
            printf("Expected: %d\n", f_gold(param0[i], param1[i], param2[i]));
            printf("Got: %d\n", f_filled(param0[i], param1[i], param2[i]));
            return -1;
        }
if (n_success != len(param0)) return -1;
    return 0;
}