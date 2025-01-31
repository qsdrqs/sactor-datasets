#include<stdio.h>
#include<string.h>

char str[201];
char former[101];
char latter[101];
int main(void) {
 int i, j;
 int Len;
 int len;
 int flag;
 scanf("%s", str);
 Len = strlen(str);//改入力した文字列の改行文字を除く長さ//
 len = Len;
 for (i = 1; i <= Len / 2 - 1; i++) {
  flag = 0;
  len = len - 2;
  for (j = 1; j <= len / 2; j++) {
   former[j] = str[j];
   latter[j] = str[len / 2 + j];
   if (former[j] != latter[j]) {
    flag = 1;
    break;
   }
   if (flag == 0) {
    printf("%d", len);
    return 0;
   }
  }
 }
 return 0;
}
