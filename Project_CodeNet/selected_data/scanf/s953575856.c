#include <stdio.h>

int main(){
 int n,m,i,j;
 char c,s[22]="{{{{{{{{{{{{{{{{{{{{{";
 n = 21;
 scanf("%d",&m);
 if(m!=0){
  scanf("\n");
  for(i=0;i<m;i++){
   for(j=0;;j++){
    scanf("%c",&c);
    if(c=='\n'|| c < 'a' || c > 'z'){
     break;
    } else if(c > s[j] || j > n-1 ){
     while(scanf("%c",&c),c != '\n');
     break;
    } else if(c < s[j]){
     s[j++] = c;
     while(scanf("%c",&s[j]),s[j++] != '\n');
     n = j-1;
     break;
    }
   }
  }
  for(i=0;i<n;i++) printf("%c",s[i]);
 }
 printf("\n");
 return 0;
}
