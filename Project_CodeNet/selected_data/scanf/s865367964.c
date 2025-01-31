#include<stdio.h>
#include<string.h>

int main(){
  int i,flag[26]={},j,flag1=0;
  char s[26],ss[26];
  scanf("%s",s);
  for(i=0;i<strlen(s);i++){
    flag[s[i]-'a']=1;
  }
  if(strlen(s)!=26){
    for(i=0;i<26;i++){
      if(!flag[i]){
        printf("%s%c\n",s,i+'a');
        break;
      }
    }
  }
  else{
    for(i=0;i<strlen(s);i++){
      flag[s[i]-'a']=i;
    }
    for(i=24;i>=0;i--){
      if(flag[s[i]-'a'+1]>=i&&s[i]-'a'+1<26){
        for(j=0;j<i;j++) printf("%c",s[j]);
        printf("%c\n",s[i]+1);
        flag1=1;
        break;
      }
    }
    if(!flag1) printf("-1\n");
  }
}
