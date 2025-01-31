#include <stdio.h>

int main(){
  char p[101],s[101];
  int i=0,j=0,k=0,l=0,m=0;
  int ans=0;
  for(i=0; i<101; i++){
    scanf("%c",&s[i]);
    if(s[i]=='\n')break;
  }
  for(j=0; j<101; j++){
    scanf("%c",&p[j]);
    if(p[j]=='\n')break;
  }
  for(k=0;k<i;k++){
    if(s[k]==p[0]){
      for(l=0; l<j; l++){
        m=k+l;
        if(m>=i)m-=i;
        if(s[m]!=p[l])break;
        if(l==j-1)ans=1;
      }
    }
  }
  if(ans)printf("Yes\n");
  else printf("No\n");
  return 0;
}
