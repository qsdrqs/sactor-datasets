#include<stdio.h>

int main(){

   int i,j,n;
   int count = 0;
   scanf("%d",&n);

   int a[n];

  for(i = 0; i < n; i++){

   scanf("%d",&a[i]);

}

  for(i = 0; i < n; i++){

  for(j = n-1; j >= i; j--){

   if(a[j] < a[j-1]){

    int tmp = a[j];

    a[j] = a[j-1];

    a[j-1] = tmp;

     count++;

   }

}

}

   for(i = 0; i < n-1; i++)

    printf("%d",a[i]);

    printf("%d\n%d\n",a[n-1],count);

  return 0;

 }