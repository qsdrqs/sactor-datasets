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

int f_gold ( char tree [], int k ) {
  int level = - 1;
  int product = 1;
  int n = strlen(tree);
  for ( int i = 0;
  i < n;
  i ++ ) {
    if ( tree [ i ] == '(' ) level ++;
    else if ( tree [ i ] == ')' ) level --;
    else {
      if ( level == k ) product *= ( tree [ i ] - '0' );
    }
  }
  return product;
}


int f_filled ( char tree [], int k ) {
  int level = - 1;
  int product = 1;
  int n = strlen(tree);
  for ( int i = 0;
  i < n;
  i ++ ) {
    if ( tree [ i ] == '(' ) level ++;
    else if ( tree [ i ] == ')' ) level --;
    else {
      if ( level == k ) product *= ( tree [ i ] - '0' );
    }
  }
  return product;
}


int main(int argc, char *argv[]) {
    int n_success = 0;
    char param0[][100] = {
    "(0(5(6()())(4()(9()())))(7(1()())(3()())))",
    "(8(3(2()())(6(5()())()))(5(10()())(7(13()())())))",
    "(0(5(6()())(4()(9()())))(7(1()())(3()())))",
    "(8(3(2()())(6(5()())()))(5(10()())(7(13()())())))",
    "(8(3(2()())(6(5()())()))(5(10()())(7(13()())())))",
    "(8(3(2()())(6(5()())()))(5(10()())(7(13()())())))",
    "(0(5(6()())(4()(9()())))(7(1()())(3()())))",
    "(0(5(6()())(4()(9()())))(7(1()())(3()())))",
    "0010",
    "kjtdgmy"};
    int param1[] = {2,3,1,2,4,100,3,0,12,97};
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