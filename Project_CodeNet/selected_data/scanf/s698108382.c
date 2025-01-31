#include<stdio.h>
#include<string.h>

char H[1000000][14]; /* Hash Table */
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
int h1(int key){
  key %= 1000000;
  return key;
}
int h2(int key){
  key = 1 + key % (1000000 - 1);
  return key;
}
int find(char str[]){
  int key1, key2;
  key1 = h1(getKey(str));
  key2 = h2(getKey(str));
  while(H[key1][0] != ((void *)0)){
    if(strcmp(H[key1],str) == 0){
      return 1;
    }
    else{
      key1 += key2;
      if(key1 > 1000000){
 key1 -= 1000000;
      }
      continue;
    }
  }
  return (-1);
}
int insert(char str[]){
  int key1, key2;
  key1 = h1(getKey(str));
  key2 = h2(getKey(str));
  while(1){
    if(H[key1][0] == ((void *)0)||strcmp(H[key1],str) == 0){
      strcpy(H[key1],str);
      break;
    }
    else{
      key1 += key2;
      if(key1 > 1000000){
 key1 -= 1000000;
      }
      continue;
    }
  }
  return 1;
}
int main(){
    int i, n, h;
    char str[14], com[9];
    scanf("%d", &n);
    for ( i = 0; i < n; i++ ){
 scanf("%s %s", com, str);
 if ( com[0] == 'i' ){
     insert(str);
 } else {
     if (find(str) == 1){
  printf("yes\n");
     } else {
  printf("no\n");
     }
 }
    }
    return 0;
}
