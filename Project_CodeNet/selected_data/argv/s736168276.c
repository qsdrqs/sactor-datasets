
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
 //#############################
 // arg check
 //#############################
 if (argc == 1)return 1;
 if (argc >= 4)return 1;
 int int_a = atoi(argv[1]);
 int int_b = atoi(argv[2]);
 int i, j;
 int flag_calc = 0;
 int sum = int_a + int_b;
//	printf("%d,%d,%d", int_a, int_b,sum);
 if (int_a == 0)return 1;
 if (int_b == 0)return 1;
 if ((int_a > 16)||(int_a < 1))return 1;
 if ((int_b > 16) || (int_b < 1))return 1;
 if (sum >= 17)return 1;
 //#############################
 //body
 //#############################
//	puts("point1");
 int cake[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 for (i = 15; ((i >= 0) && (int_a >= 1)); ) {
  cake[i] = 1;
  int_a--;
  i = i - 2;
 }
 for (j = 15; ((j >= 0) && (int_b >= 1)); ) {
  if (cake[j] == 1) {
   j = j - 1;
  }else if (cake[j] == 0) {
    cake[j] = 1;
    int_b--;
    j = j - 2;
  }
 }
 //#############################
 // result
 //#############################
 if ((int_a == 0) && (int_b == 0))flag_calc = 1;
 switch (flag_calc) {
 case 1:
  puts("Yay!");
  break;
 case 0:
  puts(":(");
  break;
 default:
  break;
 }
 return 0;
}
