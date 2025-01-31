#include<stdio.h>
#include<stdlib.h>

int count = 0;

int countt(int num);

int main(int argc, char *argv[]) {
        int N;
        int max = 0, num = 1, i;

        N = atoi(argv[1]);

        for(i = 0; i <= N; i++) {
                count = 0;
                countt(i);
                if(max < count) {
                        max = count;
                        num = i;
                }
        }

        printf("%d", num);

        return 0;

}

int countt(int num) {
        if((num % 2 == 0) && (num != 0)) {
                count++;
                countt(num / 2);
                return 0;
        }
        else
                return -1;
}