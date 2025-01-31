#include <stdio.h>
#include <stdlib.h>

int DigitSum(int N){
    int digit,sum;
    do{
        digit = N % 10;
        N -= digit;
        N /= 10;
        sum += digit;
    }while(N==0);
    return sum;
}
int main(int argc, char * argv[]){
    long int N = atoi(argv[1]);
    if(N % DigitSum(N)==0){
        printf("Yes");
    } else {
        printf("No");
    }
    return 0;
}
