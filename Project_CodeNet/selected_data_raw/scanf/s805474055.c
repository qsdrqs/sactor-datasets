#include <stdio.h>

int main(){
  char S[500000];
  scanf("%s",S);
  int i;
  for(i=0;S[i]!='\0';i++);
  int N=i+1;
  int A[N];
  int c1=0,c2=0;
  for(i=0;i<N;i++){
    if(S[i]=='<'){
      c1++;
    }else if(S[i]=='>'){
      c2++;
    }
    if((S[i]=='>'&&S[i+1]=='<')||S[i+1]=='\0'){
      for(int j=0;j<c1;j++){
        A[i-c1-c2+1+j]=j;
      }
      if(c1>=c2) A[i-c2+1]=c1;
      if(c1<c2) A[i-c2+1]=c2;
      for(int j=0;j<c2;j++){
        A[i+1-j]=j;
      }
    c1=c2=0;
    }
  }
  int sum=0;
  for(i=0;i<N;i++){
    sum+=A[i];
  }
  printf("%d",sum);
  return 0;
}