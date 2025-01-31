#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  // argsは引数の数。argvは実際の値
  // argv[0]にはプログラム自身の名前が必ず入るので、最小数は１
  if (argc != 4) {
    printf("Error\n");
    return -1;
  }
  int P = atoi(argv[1]);
  int Q = atoi(argv[2]);
  int R = atoi(argv[3]);
  // 第二引数は数字だがchar型であるのでintに変換
  int i = 0;
  int answer = fmin(fmin(P + Q, Q + R), R + P);
  printf("%d\n", answer);
  return 0;
}
