#include <stdio.h>
#include <string.h>

char fizz[5]={"Fizz"};
char buzz[5]={"Buzz"};
char fizzbuzz[9]={"FizzBuzz"};
int main() {
  int n,m;
  int i,j,k,c,d;
  while(1) {
    int p[1001] = {0};
    scanf("%d %d",&n,&m);
    if(n==0 && m==0) break;
    for(i=0;i<n; i++) p[i] = 1;
    c = 0;
    d = 0;
    for(i=1;i<=m;i++) {
      char s[10]={};
      while(1) {
 if(p[c] == 1)break;
 c=(c+1)%n;
      }
      scanf("%s",s);
      //   printf("%d %s\n",c,s);
      if(n - d == 1) continue;
      int flg=0;
      if(i % 15 == 0 ) {
 if( strcmp(s,fizzbuzz) == 0 )flg=1;
      }else if(i%5==0){
 //if( strcmp(s,buzz) == 0 )flg=1;
 if(s[0]=='B')flg=1;
      }else if(i%3==0){
 if( strcmp(s,fizz) == 0 )flg=1;
 //if(s[0]=='F'&&s[4]!='B')flg=1;
      }else{
 k = 0;
 for(j=0;j < strlen(s); j++){
   k = (s[j]-'0')+k*10;
 }
 if(k == i)flg=1;
      }
      if(flg==0){
 p[c]=0;
 d++;
      }
      c=(c+1)%n;
    }
    int x=0;
    for(i=0;i<n; i++){
      if(p[i] == 1) {
 if(x>0)printf(" ");
 x=1;
 printf("%d",i+1);
      }
    }
    printf("\n");
  }
  return 0;
}
