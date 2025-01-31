#include <stdio.h>

int main(void)
{

  int h,w;

  for(;;){
    scanf("%d %d",&h,&w);
    if(h==0&&w==0)break;
    int i,j;

    for(i=1;i<=w;i++)printf("#");
    putchar('\n');

    for(j=1;j<=h-2;j++){
      printf("#");
      for(i=1;i<=w-2;i++)printf(".");
      printf("#");
      putchar('\n');
      }

    for(i=1;i<=w;i++)printf("#");
    puts("\n");
  }
  return 0;
}