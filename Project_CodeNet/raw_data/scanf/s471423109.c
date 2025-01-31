#include <stdio.h>
int prime[10001];
int twin_prime[10001];

void isprime(int n) {
    int i, k, l = 0, p1, q1;
    for(int i = 2; i <= n; i++) {
        prime[i] = 1;
        for(k = 2; k < i; k++) {
            if(i%k == 0) prime[i] = 0;
        }
        if(prime[i]) {
            twin_prime[l] = i;
            l++;
        }
    }
    for(i = 0; i < l; i++) {
        if(twin_prime[i+1]-twin_prime[i]==2) {
            p1 = twin_prime[i];
            q1 = twin_prime[i+1];
        }
    }
    printf("%d %d\n", p1, q1);
}

int main() {
    int i, n;
    for(i = 0; i < 10000; i++) {
        scanf("%d", &n);
        if(n == 0) break;
        isprime(n);
    }
    return 0;
}