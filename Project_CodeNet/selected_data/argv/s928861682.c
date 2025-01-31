/*
        leapyear.c
        閏年判定プログラム
*/

/* インクルードヘッダ */
#include <stdio.h>
#include <stdlib.h>

/* プロトタイプ宣言 */
int isLeapYear(int y);
/*
        メイン
*/
int main(int argc, char *argv[])
{
        int year = 0;
        /* 引数のチェック */
        if (argc < 2) {
                /* 引数が指定されていない場合は */
                /* 使用方法を表示して処理終了 */
                printf("Usage: %s <year>¥n", argv[0]);
                return 0;
        }
        /* 第一引数を西暦年として取得,atoi()でintに変換 */
        year = atoi(argv[1]);
        /* 年を出力 */
        printf("西暦%d年は", year);
        /* もし年が閏年なら */
        if (isLeapYear(year)) {
                /* '閏年です'と出力 */
                printf("%s¥n", "閏年です。");
        } else {
                /* そうでなければ */
                /* '閏年ではありません'と出力 */
                printf("%s¥n", "閏年ではありません。");
        }
        return 0;
}
/*
        閏年判定
        isLeapYear
        
        <概要>
        指定された西暦年が閏年かどうかを判定する。
        <戻り値>
        1:閏年
        0:閏年ではない
        <引数>
        int y:(i)西暦年
*/
int isLeapYear(int y)
{
        int r = 0;
        /* 西暦年が4で割り切れ,かつ100で割り切れない年は閏年 */
        /* または400で割り切れる年は閏年 */
        if (y % 4 == 0 && y % 100 != 0 || y % 400 == 0) {
                r = 1;
        } else {
                r = 0;
        }
        return r;
}
