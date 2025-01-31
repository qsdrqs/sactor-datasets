#include <stdio.h>
#include <string.h>

typedef struct {
    int x;
    int y;
} POINT;
int main(void)
{
    POINT data[3000];
    static char exist[5001][5001];
    int i, j;
    int n;
    int max;
    int dx, dy;
    while (1){
        scanf("%d", &n);
        if (n == 0){
            break;
        }
        memset(exist, 0, sizeof(exist));
        for (i = 0; i < n; i++){
            scanf("%d%d", &data[i].x, &data[i].y);
            exist[data[i].x][data[i].y] = 1;
        }
        max = 0;
        for (i = 0; i < n; i++){
            for (j = i + 1; j < n; j++){
                if (i == j){
                    continue;
                }
                dx = data[j].x - data[i].x;
                dy = data[j].y - data[i].y;
                if (dx < 0){
                    dx *= -1;
                }
                if (dy < 0){
                    dy *= -1;
                }
                if (data[i].x + dy <= 5000 && data[i].y + dx <= 5000 &&
                        data[j].x + dy <= 5000 && data[i].y + dx <= 5000 &&
                            exist[data[i].x + dy][data[i].y + dx] && exist[data[j].x + dy][data[j].y + dx] && dx * dx + dy * dy > max){
                    max = dx * dx + dy * dy;
                }
            }
        }
        printf("%d\n", max);
    }
    return (0);
}
