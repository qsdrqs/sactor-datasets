#include<stdio.h>
#include <string.h>
struct Card{
  char suit[3];
  char value;
};
void bubble(struct Card[] ,int );
void selection(struct Card[],int);
void print(struct Card[] ,int );
int isStable(struct Card[] , struct Card[],int );



void bubble(struct Card A[],int N){
  int i,j;
  
  struct Card temp;
  for(i=0;i<N;i++){
    for(j=N-1;j>=i+1;j--){
      if(A[j].value<A[j-1].value){
	temp=A[j];
	A[j]=A[j-1];
	A[j-1]=temp;
      }
    }
  }
}

void selection(struct Card A[],int N){
  int i,j,minj;
  struct Card temp;

  for(i=0;i<N;i++){
    minj=i;
    
    for(j=i;j<N;j++){
      if(A[j].value<A[minj].value)minj=j;
    }
    
    temp=A[i];
    A[i]=A[minj];
    A[minj]=temp;
  }
}

void print(struct Card A[],int N){
  int i;
  
  for(i=0;i<N;i++){
    if(i>0)printf(" ");
    printf("%s",A[i].suit);
  }
 
  printf("\n");
}

int isStable(struct Card C1[], struct Card C2[],int N){
  int i;
  
  for(i=0;i<N;i++){
    if(strcmp(C1[i].suit,C2[i].suit)!=0)return 0;
  }
  return 1;
}

int main(){
  struct Card C1[100],C2[100];
  int n;
  int i;
  char ch;

  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%s",&C1[i].suit);
  }

  for(i=0;i<n;i++){
    C1[i].value=C1[i].suit[1];
    
    C2[i]=C1[i];
  }
  
  bubble(C1,n);
  selection(C2,n);

  print(C1,n);

  printf("Stable\n");
  print(C2,n);
  if( isStable(C1,C2,n)==1){
    printf("Stable\n");
  }
  else printf("Not stable\n");
  return 0;
}

      

