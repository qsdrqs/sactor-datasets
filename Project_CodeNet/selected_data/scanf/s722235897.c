#include<stdio.h>
#include<string.h>

char H[100][14]; /* Hash Table */
int getChar(char ch){
  if ( ch == 'A') return 1;
  else if ( ch == 'C') return 2;
  else if ( ch == 'G') return 3;
  else return 4;
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
int h1(int key){ return key%100; }
int h2(int key){ return 1 + (key%(100 -1)); }
int find(char str[]){
  long long key;
  int a1,a2,h3;
  int i=0;
  key = getKey(str);
  a1 = h1(key);
  a2 = h2(key);
  while(1){
    h3 =(a1 +i*a2)%100;
    if(strcmp(str,H[h3])==0) return 1;
    if((h3==a1) || (H[h3][0] == '\0')) return 0;
    if(100<=h3) h3 = h3-100;
    i++;
  }
}
void insert(char str[]){
  long long key;
  int a1,a2,h3;
  int i=0;
  key = getKey(str);
  a1=h1(key);
  a2=h2(key);
  while(1){
    h3 =(a1 +i*a2)%100;
    if(100 <= h3) h3 = h3-100;
    if(H[h3][0] == '\0') break;
    i++;
  }
  strcpy(H[a1],str);
}
int main(){
  int i, n, h;
  char str[14], com[9];
  for ( i = 0; i < 100; i++ ) H[i][0] = '\0';
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
