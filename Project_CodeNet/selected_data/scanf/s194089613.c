#include<stdio.h>
#include<stdlib.h>

typedef struct minimum{
  int min;
  struct minimum *next;
} Min;
Min *head=((void *)0);
Min *tail=((void *)0);
Min *createNode(void){
  Min *new;
  new=(Min *)malloc(sizeof(Min));
  return new;
};
void addNodeToList(int number){
  Min *newMin=createNode();
  newMin->min=number;
  if(head==((void *)0) && tail==((void *)0)){
    head=newMin;
    tail=newMin;
  }else{
    tail->next=newMin;
    tail=newMin;
  }
  tail->next=((void *)0);
}
int main(){
  int n;
  scanf("%d", &n);
  int a[n],i;
  for(i=0;i<n;i++){
    scanf("%d", &a[i]);
  }
  int count=0, check;
  Min *current=((void *)0);
  for(i=n-1;i>=0;i--){
    check=0;
    current=head;
    while(current!=((void *)0)){
      if(a[i]<current->min){
        current->min=a[i];
        check=1;
        break;
      }
      current=current->next;
    }
    if(check==0){
      addNodeToList(a[i]);
      count++;
    }
  }
  printf("%d", count);
  return 0;
}
