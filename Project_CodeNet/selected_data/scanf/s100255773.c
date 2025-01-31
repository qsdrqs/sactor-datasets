#include <stdio.h>
#include <stdlib.h>

int main(void) {
 int n, t, x, y, ct, cx, cy, can;
 ct = cx = cy = 0;
 can = 1;
 scanf("%d", &n);
 for (int i = 0; i < n; i++) {
  scanf("%d %d %d", &t, &x, &y);
  if (!can) continue;
  int difT = t - ct;
  int difPos = abs(x - cx) + abs(y - cy);
  if (difT >= difPos && (difT - difPos) % 2 == 0)
  {
   ct = t;
   cx = x;
   cy = y;
  }
  else
  {
   can = 0;
  }
 }
 if (can)
 {
  printf("YES\n");
 }
 else
 {
  printf("NO\n");
 }
 return 0;
}
