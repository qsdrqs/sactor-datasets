#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
 if(argc != 3 +1){
  return -1;
 }
 char * p1 = argv[1];
 char * p2 = argv[3];
 char * op = argv[2];
 //try
 //Integer.valueOf()
 unsigned long long p1_i = atol(p1);
 unsigned long long p2_i = atol(p2);
 unsigned long long res = 0;//subtraction can cause negative values
 //return if p1, p2 arent integers
 //check range of p1, p2
 //or if op isnt - or +
 if(strcmp(op,"-")==0)
 {
  res = p1_i - p2_i;
 }else if(strcmp(op,"+")==0)
 {
  res = p1_i + p2_i;
 }else{
  return -1;
 }
 return res;
}
