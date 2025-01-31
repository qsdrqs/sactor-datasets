#include<stdio.h>

int p[1000] = { 0 };
int first, second, third;
int sort(int k) {
    int i, j;
    first = p[0]; second = p[1]; third = p[2];
    for (i = 1; i < k; i++) {
        if (first >= p[i]) {
            first = p[i];
        }
        else if (second >= p[i]) {
            second = p[i];
        }
        else if (third >= p[i]) {
            third = p[i];
        }
    }
    return 0;
}
int main(void) {
    int n, k, i,ans=0;
    scanf("%d %d", &n, &k);
    for (i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }
    sort(n);
        ans += first;
        ans += second;
        ans += third;
    printf("%d", ans);
    return 0;
}
