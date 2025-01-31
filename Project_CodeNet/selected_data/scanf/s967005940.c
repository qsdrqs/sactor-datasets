#include<stdio.h>

struct process{
  char name[10];
  int time;
};
struct process p[100000];
int head,tail;
void enqueue(struct process x){
  p[tail] = x;
  if(tail+1==100000) tail = 0;
  else tail++;
}
struct process dequeue(){
  struct process y;
  y = p[head];
  if(head+1 == 100000) head = 0;
  else head++;
  return y;
}
int main(void){
  int n,q;
  int i;
  int t = 0;
  struct process tmp;
  scanf("%d", &n);
  scanf("%d", &q);
  //  printf("n = %d, q = %d\n",n,q);
  for(i=0; i<n; i++){
    scanf("%s", p[i].name);
    scanf("%d", &p[i].time);
  }
  /*
  for(i=0; i<n; i++){
    printf("%s %d\n", p[i].name, p[i].time);
  }
  */
  head = 0;
  tail = n;
  while(1){
    if(head==tail) break;
    tmp = dequeue();
    if(tmp.time <= q){//??????time???q??\?????????
      t += tmp.time;
      printf("%s %d\n", tmp.name, t);
    }
    else{
      tmp.time -= q;
      t += q;
      enqueue(tmp);
    }
  }
  return 0;
}
