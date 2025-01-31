#include<stdio.h>
int main()
{
    int a,b,c,f=0;
    // 整数の入力
    // スペース区切りの整数の入力
    scanf("%d %d %d",&a,&b,&c);
    // 出力
  for(int i=1;i<=b;i++){
    if((a*i-c)%b==0){
      printf("YES");
      f=1;
      break;
    }
  }
    if(f==0)printf("NO");
    return 0;
}