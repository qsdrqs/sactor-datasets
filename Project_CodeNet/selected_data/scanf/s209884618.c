#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct card {
 char Rc[3],Rcc[3];//　重大注意！！！:配列の数はEOS（空白分も入れ無くてはならない）
 int R,Ri;
};
int SelectionSort(struct card R[], int N);
int BubbleSort(struct card R[], int N);
void Swap(int *a, int *b, char aa[], char bb[]);
void isStable(struct card c[], int N);
int main(void) {
 int N ;
 char p;
 scanf("%d\n", &N);//半角スペースで区切ることができる。
 struct card c[36];
 int t, k;
 for (t = 0; t < N; t++) {scanf("%s", &c[t].Rc);}
 for (t = 0; t < N; t++) {
  p = c[t].Rc[1];
  c[t].R = atoi(&p);
  strcpy(c[t].Rcc, c[t].Rc);
  c[t].Ri = c[t].R;
 }
 BubbleSort(c, N);
 for (k = 0; k < N; k++) {
  if (k > 0) {
   printf(" "); }
  printf("%s", c[k].Rc);
 }
 isStable(c,N);
 for (t = 0; t < N; t++) {
  strcpy(c[t].Rc, c[t].Rcc);
  c[t].R = c[t].Ri;
 }
 SelectionSort(c, N);
 for (k = 0; k < N; k++) {
  if (k > 0) {
   printf(" ");
  }
  printf("%s", c[k].Rc);
 }
 isStable(c, N);
 return 0;
}
int SelectionSort(struct card c[], int N) {
 int i, j, minj;
 int count = 0;
 for (i = 0; i < N - 1; i++) {
  minj = i;
  for (j = i; j < N; j++) {
   if (c[j].R < c[minj].R) {
    minj = j;
   }
  }
  Swap(&c[i].R, &c[minj].R, c[i].Rc, c[minj].Rc);
  if (i != minj) {
   count++;
  }
 }
 return count;
}
int BubbleSort(struct card c[], int N) {
 int flag = 1;
 int count = 0;
 int j;
 while (flag != 0) { //forにして、ソートを終える場所を少しづつ変えていけば完璧。（恐らくオーダーは変わらない。）
  flag = 0;
  for (j = N - 1; j >= 1; j--) {
   if (c[j].R < c[j-1].R) {
    Swap(&c[j].R, &c[j - 1].R, c[j].Rc, c[j - 1].Rc);
    flag = 1;
    count++;
   }
  }
 }
 return count;
}
void Swap(int *a, int *b,char aa[] ,char bb[]){
 int k,i;
 char t[2];
 k = *a;
 *a = *b;
 *b = k;
 for (i = 0; i < 2; i++) {
  t[i] = aa[i];
  aa[i] = bb[i];
  bb[i] = t[i];
 }
}
void isStable(struct card c[], int N) {
 int i, j, a, b;
 for (i = 0; i < N; i++) {
  for (j = i + 1; j < N; j++) {
   for (a = 0; a < N; a++) {
    for (b = a + 1; b < N; b++) {
     if (c[j].Ri == c[i].Ri && strcmp(c[i].Rcc,c[b].Rc) == 0 && strcmp(c[j].Rcc,c[a].Rc) == 0){
      printf("\nNot Stable\n");
      return ;
     }
    }
   }
  }
 }
 printf("\nStable \n");
 return ;
}
