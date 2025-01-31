#include <stdio.h>

typedef struct {
    int state[2][7];
    int assign[7];
    int p; // 次に代入すべきインデックス
} dice;

int rot[6][7] = {
    {0,1,2,3,4,5,6},
    {0,2,6,3,4,1,5},
    {0,4,2,1,6,5,3},
    {0,3,2,6,1,5,4},
    {0,5,1,3,4,6,2},
    {0,1,3,5,2,4,6},
};
int tr['Z'];
char str[6] = "NEEEN";

void dice_init(dice *d, int *a) {
    int i;
    int t[6] = {0, 'N', 'E', 'W', 'S', 'L'};
    for (i = 1; i <= 6; i++) d->assign[i] = a[i];
    for (i = 1; i <= 5; i++) tr[t[i]] = i;
    for (i = 1; i <= 6; i++) d->state[0][i] = rot[0][i];
    d->p = 1;
}

int get_d_num(dice *d, int i) {
    return d->assign[d->state[!(d->p)][i]];
}

void dice_rotate(dice *d, char dir) {
    int i;
    for (i = 1; i <= 6; i++) {
        d->state[d->p][i] = d->state[!(d->p)][rot[tr[dir]][i]];
    }
    d->p = !(d->p);
}

void set_top(dice *d, int t) {
    char s[] = "NEEEN";
    char *ps = s;
    while (*ps) {
        if (get_d_num(d, 1) == t) return;
        dice_rotate(d, *ps);
        ps++;
    }
}

void set_front(dice *d, int f) {
    while (get_d_num(d, 2) != f) dice_rotate(d, 'L');
}

int sub_equals(dice *d1, dice *d2) {
    int i;
    for (i = 1; i <= 6; i++) {
        if (get_d_num(d1, i) != get_d_num(d2, i)) return 0;
    }
    return 1;
}

int dice_equals(dice *d1, dice *d2) {
    int i, j;
    char *p = str;
    for (i = 1; i<= 6; i++) {
        for (j = 1; j <= 4; j++) {
            if (sub_equals(d1, d2)) {
                return 1;
            }
            dice_rotate(d2, 'L');
        }
        dice_rotate(d2, *p);
        p++;
    }
    return 0;
}

dice d[100];
int a[100][7];
int main(void) {
    int n, i, j;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        for (j = 1; j <= 6; j++) scanf("%d", a[i] + j);
        dice_init(d + i, a[i]);
    }
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (dice_equals(d + i, d + j)) {
                printf("No\n");
                return 0;
            }
        }
    }
    printf("Yes\n");
    return 0;
}

