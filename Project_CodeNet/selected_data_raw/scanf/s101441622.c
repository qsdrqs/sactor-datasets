#include<stdio.h>
#include<string.h>
#include <math.h>
#include <stdlib.h>
#define MAX 10000


typedef struct{
  int p;
  int r;
  int l;
  int s;
} Node;
int flag;
int hfunc(Node *,int,int);
void pre(Node *,int);
void in(Node *,int);
void pos(Node *,int);

int main(){
  int n,i,j,degree,point,c1,c2,depth=0,sum=0,height,root=0;
 
  Node T[25];
  for(i=0;i<25;i++){
    T[i].p=T[i].r=T[i].l=T[i].s=-1;
  }
  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%d%d%d",&point,&c1,&c2);
    if(c1!=-1)sum++;
    if(c2!=-1)sum++;
    T[point].l=c1;
    T[point].r=c2;
    if(c1!=-1){
    T[c1].s=c2;
    T[c1].p=point;
    }
    if(c2!=-1){
    T[c2].s=c1;
    T[c2].p=point;
    }
  }
  for(i=0;i<=sum;i++){
    if(T[i].p==-1){root=i; break;}
  }
  printf("Preorder\n");
  pre(T,root);
  printf("\nInorder\n");
  in(T,root);
  printf("\nPostorder\n");
  pos(T,root);
  printf("\n");
    

  

  return 0;
}
void pre(Node T[],int i){
  if(T[i].l==-1 && T[i].r==-1){
    printf(" %d",i);
    return;
  }
  printf(" %d",i);
  if(T[i].l!=-1)
  pre(T,T[i].l);
  if(T[i].r!=-1)
  pre(T,T[i].r);
}
void in(Node T[],int i){
  if(T[i].l==-1 && T[i].r==-1)
  {
    printf(" %d",i);
    return;
  }
  if(T[i].l!=-1)
  in(T,T[i].l);
  printf(" %d",i);
  if(T[i].r!=-1)
  in(T,T[i].r);
}
void pos(Node T[],int i){
  if(T[i].l==-1 && T[i].r==-1)
    {
      printf(" %d",i);
      return;
    }
  if(T[i].l!=-1)
  pos(T,T[i].l);
  if(T[i].r!=-1)
  pos(T,T[i].r);
  printf(" %d",i);
}    

