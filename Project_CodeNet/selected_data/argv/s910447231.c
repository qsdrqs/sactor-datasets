#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[]){
 int x=0,y;
 int i,j;
 char* work;
 for(j=2;j<argc;j++){
  for(i=2;i<argc;i++){
   y=atoi(argv[i]);
   x=atoi(argv[i-1]);
   if(x<y){
    work=argv[i];
    argv[i]=argv[i-1];
    argv[i-1]=work;
   }
  }
 }
 printf("%s\n",argv[1]);
 printf("%s\n",argv[2]);
 printf("%s\n",argv[3]);
 return 0;
}
