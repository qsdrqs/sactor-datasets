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
        exit(EXIT_FAILURE);
    }
    
    input = validate_input(argv[1]);
    if (input == LONG_MAX) {
        printf("Invalid argument.\n");
        
        exit(EXIT_FAILURE);
    }

    result = input * input * input;
    
    printf("%ld\n", result);
    
    exit(EXIT_SUCCESS);
}

/*
 * 入力値をチェック
 */
long validate_input(char *input) 
{
    long val;
    char *error;
    
    if (input == NULL) {
        return LONG_MAX;
    }
    
    errno = 0;
    val = strtol(input, &error, 10);
    
    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
            || (errno != 0 && val == 0)) {
        perror("strtol");
        return LONG_MAX;
    }

    if (*error != '\0') {
        /* Invalid value */
        return LONG_MAX;
    }

    return val;
    
}