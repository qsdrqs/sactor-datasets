#include <stdio.h>
#include <string.h>

int Hash[244140625];
char s[13];
int getChar(char);
int getKey();
int find();
void insert();
int main(){
  int n;
  char com[7];
  scanf("%d" ,&n);
  while(n--){
    scanf("%s %s" ,com ,s);
    if(com[0] == 'i'){
      insert();
    }else{
      if(find()){
 puts("yes");
      }else{
 puts("no");
      }
    }
  }
  return 0;
}
int getChar(char ch){
  if(ch == 'A'){
    return 1;
  }else if(ch == 'C'){
    return 2;
  }else if(ch == 'G'){
    return 3;
  }
  return 4;
}
int getKey(){
  int sum = 0, p = 1, i;
  for(i = 0 ; i < strlen(s) ; i++){
    sum += p*(getChar(s[i]));
    p *= 5;
  }
  return sum;
}
int find(){
  int key = getKey();
  if(Hash[key]){
    return 1;
  }
  return 0;
}
void insert(){
  Hash[getKey()] = 1;
}
