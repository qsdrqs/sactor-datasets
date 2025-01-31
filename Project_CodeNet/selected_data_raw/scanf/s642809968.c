#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int max(int a,int b){
	if(a>b)return a;
	return b;
}

int compare_char(char *a,char *b){
	return strcmp(a,b);
}

int intsort(const void *a, const void *b){
	return *(int*)b - *(int*)a;
	/*qsort(a,aの配列数,sizeof(int),intsort);*/
}

int longsort(const void *a, const void *b){
	long *A=(long *)a;
	long *B=(long *)b;
	if(*A>*B) return -1;
	if(*A<*B) return 1;
	return 0;
}

int main(){
  int i=0,N,min,cnt=0;
  char ss[200001];
  scanf("%d",&N);
  scanf("%s",ss);
  while(i<N){
    if(ss[i]=='.'){
      cnt++;
    }
    i++;
  }
  if(ss[0]=='.')cnt--;
  min=cnt;
  for(i=1;i<N;i++){
    if(ss[i]=='.')cnt--;
    if(ss[i-1]=='#')cnt++;
    if(min>cnt)min=cnt;
  }
  printf("%d\n",min);
  return 0;
}