/* ex 7_1
   riverstone */

#include <stdio.h>

//頂点を表す構造体
typedef struct point{
    int x_elem;
    int y_elem;
}point;

//関数shift_pointの定義
point shift_point(point point1,point point2){
    //point型の変数を定義
    point shift_p, direct_vector, rot_vector;

    //始点point1終点point2のベクトル
    direct_vector.x_elem=point2.x_elem-point1.x_elem;
    direct_vector.y_elem=point2.y_elem-point1.y_elem;

    //vectorを90度回転
    rot_vector.x_elem=-direct_vector.y_elem;
    rot_vector.y_elem= direct_vector.x_elem;

    //point2の隣の点の座標(point1ではない方の)
    shift_p.x_elem=point2.x_elem+rot_vector.x_elem;
    shift_p.y_elem=point2.y_elem+rot_vector.y_elem;
 
    return shift_p;
}

int main(void){
    point point1, point2, point3, point4;
    //入力を受け取る
    scanf("%d %d %d %d", &point1.x_elem, &point1.y_elem, &point2.x_elem, &point2.y_elem);

    //残り2点の座標を求める
    point3=shift_point(point1,point2);
    point4=shift_point(point2,point3);

    //出力
    printf("%d %d %d %d\n", point3.x_elem, point3.y_elem, point4.x_elem, point4.y_elem);
    return 0;
}