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
int len (int arr [ ]) {return ((int) (sizeof (arr) / sizeof (arr)[0]));}
void sort (int arr [ ], int n) {qsort (arr, n, sizeof(int), cmpfunc);}

char* f_gold(const char text[], int s) {
    int length = strlen(text);
    char* result = (char*)malloc((length + 1) * sizeof(char)); // Allocate memory for result string
    for (int i = 0; i < length; i++) {
        if (isupper(text[i])) {
            result[i] = (char)(((text[i] + s - 'A') % 26) + 'A');
        } else if (islower(text[i])) {
            result[i] = (char)(((text[i] + s - 'a') % 26) + 'a');
        } else {
            result[i] = text[i]; // Non-alphabetic characters remain unchanged
        }
    }
    result[length] = '\0'; // Null-terminate the string
    return result;
}


char* f_filled ( char text [], int s ) {}

int main(void) {
    int n_success = 0;
    char param0[][100] = {"LsvbpcviVPwq","35225904","010010","QnYd","2571694","101101011010","jb","928874","11","FbvbkMb"};
    int param1[] = {15,2,36,44,11,94,22,83,93,37};
    for(int i = 0; i < len(param0); ++i)
    {
        if(f_filled(param0[i],param1[i]) == f_gold(param0[i],param1[i]))
        {
            n_success+=1;
        }
    }
    printf("#Results:", " ", n_success, ", ", len(param0));
    return 0;
}