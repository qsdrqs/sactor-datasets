#include<stdio.h>
#include<string.h>

#define M 1000001//task
#define NIL (-1)
#define L 14

char H[M][L]; /* Hash Table */

int getChar(char ch){
  if ( ch == 'A') return 1;
  else if ( ch == 'C') return 2;
  else if ( ch == 'G') return 3;
  else if ( ch == 'T') return 4;
}

/* convert a string into an integer value */
long long getKey(char str[]){
  long long sum = 0, p = 1, i;
  for ( i = 0; i < strlen(str); i++ ){
    sum += p*(getChar(str[i]));
    p *= 5;
  }
  return sum;
}

int h1(int key){ return key%M; }//task
int h2(int key){ return 1+key%(M-1); }//task

int find(char str[]){//task
  int i=0,j;
  while(1){
    j=(h1(getKey(str))+i*h2(getKey(str)))%M;
    if(H[j]!=NULL){
      if(strcmp(H[j],str)==0){
	break;
      }
      else i++;
    }
    else{
      return 0;
      break;
    }
  }
}

int insert(char str[]){//task
  int i=0,j;
  while(1){
    j=(h1(getKey(str))+i*h2(getKey(str)))%M;
    if(H[j]==NULL){
      strcpy(H[j],str);
      break;
    }
    else i++;
  }
}

int main(){
    int i, n, h;
    char str[L], com[9];
    for ( i = 0; i < M; i++ ) H[i][0] = '\0';
    
    scanf("%d", &n);
    
    for ( i = 0; i < n; i++ ){
	scanf("%s %s", com, str);
	
	if ( com[0] == 'i' ){
	    insert(str);
	} else {
	    if (find(str)){
		printf("yes\n");
	    } else {
		printf("no\n");
	    }
	}
    }

    return 0;
}