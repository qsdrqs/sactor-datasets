/* ex4_3
   kohei0713 */

#include <stdio.h>

int calculateSnowfall(int westHeight, int eastHeight);

int main(void){
    
    int westHeight, eastHeight;
    
    //input
    scanf("%d %d", &westHeight, &eastHeight);

    //関数calculateSnowfallの値をanswerに
    int answer = calculateSnowfall(westHeight, eastHeight);

    //answerを表示
    printf("%d\n", answer);

    return 0;
}

int calculateSnowfall(int westHeight, int eastHeight){
    //西と東の塔の高さの差を計算
    int height = eastHeight - westHeight;
    int westTowerHeight;

    //西の塔の高さを計算
    for(int i = 1; i < height; i++){
        westTowerHeight = westTowerHeight + i;
    }

    //雪の高さを計算
    int snowfall = westTowerHeight - westHeight;

    //雪の高さを返す
    return snowfall;
}