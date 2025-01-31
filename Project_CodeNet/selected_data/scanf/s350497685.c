#include <stdio.h>

int A[20000000];
int n;
int count(){//????´??????°?????°??????
  int i;
  for(i=1;A[i]!=0;i++){
  }
  return i;
}
void maxHeapify( int i )
{
  int l,r,large,tmp,k;
  l=2*i;
  r=2*i+1;
  if(l<= n && A[l] > A[i]) large=l;
  else large=i;
  if(r<= n && A[r] > A[large]) large=r;
  if(large!=i){
    tmp=A[i];
    A[i]=A[large];
    A[large]=tmp;
    maxHeapify(large);
  }
}
void increaseKey(int n,int k){
  int tmp;
  A[n]=k;
  while(n>1 && A[n/2] < A[n]){
    tmp=A[n];
    A[n/2]=A[n];
    n=n/2;
  }
}
void insert(int k){
  int i;
  //i=count();
 n++;
  A[n]=-100000000;
  //n++;
  increaseKey(n,k);
}
int extractMax(){
  int i,max;
   maxHeapify(1);
  //n=count();
  max=A[1];
  A[1]=A[n];
  //printf("A[n]=%d\n",A[n]);
  n--;
  maxHeapify(1);
  return max;
}
int main(){
  int i, x;
  char com[20];
  for ( i = 1; i <= 2000000; i++ ){
    scanf("%s", com);
    if ( com[0] == 'i' ){
      scanf("%d", &x);
      insert(x);
    }
     else if ( com[1] == 'x' ){
       printf("%d\n",extractMax());
    }
     else if ( com[1] == 'n' ) break;
  }
  return 0;
}
