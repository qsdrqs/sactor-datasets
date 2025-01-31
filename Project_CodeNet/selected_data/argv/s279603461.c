#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <math.h>

long validate_input(char *input);
int main(int argc, char *argv[])
{
    long input;
    long result;
    /* Check argument num */
    if (argc != 2) {
        exit(1);
    }
    input = validate_input(argv[1]);
    if (input == 0x7fffffffffffffffL) {
        printf("Invalid argument.\n");
        exit(1);
    }
    result = input * input * input;
    printf("%ld\n", result);
    exit(0);
}
/*
 * 入力値をチェック
 */
long validate_input(char *input)
{
    long val;
    char *error;
    if (input == ((void *)0)) {
        return 0x7fffffffffffffffL;
    }
    (*__errno_location ()) = 0;
    val = strtol(input, &error, 10);
    if (((*__errno_location ()) == 34 && (val == 0x7fffffffffffffffL || val == (-0x7fffffffffffffffL - 1L)))
            || ((*__errno_location ()) != 0 && val == 0)) {
        perror("strtol");
        return 0x7fffffffffffffffL;
    }
    if (*error != '\0') {
        /* Invalid value */
        return 0x7fffffffffffffffL;
    }
    return val;
}
