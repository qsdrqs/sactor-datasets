#include<stdio.h>

int main(){
    int n,i;
    long int total=1;


    scanf("%d", &n);

    long int a[n];

    for(i=0; i<n; i++){
      scanf("%x", &a[i]);
      total=total*a[i];
    }

    if(total>1000000000000000000){
      printf("-1\n");
    }
    else if(total==0){
      printf("0\n");
    }
    else{
      printf("%d", total);
    }

    return 0;
  }
