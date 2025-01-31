#include<stdio.h>

int H[2000001],size;
void MaxHeapify(int pos){
 int L=pos*2, R=pos*2+1,largest,tmp;
 if(L<=size && H[L]>H[pos])largest=L;
 else largest=pos;
 if(R<=size && H[R]>H[largest])largest=R;
 if(largest!=pos){
  //swap
  tmp=H[pos];
  H[pos]=H[largest];
  H[largest]=tmp;
  MaxHeapify(largest);
 }
 return;
}
void Insert(int key){
 int pos,tmp;
 H[++size]=key;
 pos=size;
 while(pos/2>0 && H[pos/2]<H[pos]){
  //swap
  tmp=H[pos];
  H[pos]=H[pos/2];
  H[pos/2]=tmp;
  pos/=2;
 }
 return;
}
int Extract(void){
 int ret=H[1];
 H[1]=H[size]; --size;
 MaxHeapify(1);
 return ret;
}
int main(){
 int k;
 char com[10];
 while(1){
  scanf("%s",com);
  if(com[0]=='i'){
   //insert
   scanf("%d",&k);
   Insert(k);
  }else{
   if(com[2]=='d')break;
   printf("%d\n",Extract());
  }
 }
 return 0;
}
