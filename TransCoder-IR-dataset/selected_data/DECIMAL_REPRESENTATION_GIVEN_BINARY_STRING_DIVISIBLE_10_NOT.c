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

bool f_gold ( char bin [] ) {
  int n = len(bin);
  if ( bin [ n - 1 ] == '1' ) return false;
  int sum = 0;
  for ( int i = n - 2;
  i >= 0;
  i -- ) {
    if ( bin [ i ] == '1' ) {
      int posFromRight = n - i - 1;
      if ( posFromRight % 4 == 1 ) sum = sum + 2;
      else if ( posFromRight % 4 == 2 ) sum = sum + 4;
      else if ( posFromRight % 4 == 3 ) sum = sum + 8;
      else if ( posFromRight % 4 == 0 ) sum = sum + 6;
    }
  }
  if ( sum % 10 == 0 ) return true;
  return false;
}


bool f_filled ( char bin [] ) {
  int n = len(bin);
  if ( bin [ n - 1 ] == '1' ) return false;
  int sum = 0;
  for ( int i = n - 2;
  i >= 0;
  i -- ) {
    if ( bin [ i ] == '1' ) {
      int posFromRight = n - i - 1;
      if ( posFromRight % 4 == 1 ) sum = sum + 2;
      else if ( posFromRight % 4 == 2 ) sum = sum + 4;
      else if ( posFromRight % 4 == 3 ) sum = sum + 8;
      else if ( posFromRight % 4 == 0 ) sum = sum + 6;
    }
  }
  if ( sum % 10 == 0 ) return true;
  return false;
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    char param0[][100] = {"101000","39613456759141","11","PoiHjo","2","0000101","T  s dZKeDX gK","3944713969","1000","ifYUgdpmt"};
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