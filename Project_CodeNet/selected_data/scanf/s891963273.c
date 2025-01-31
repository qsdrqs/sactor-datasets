#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert(int *L, long x, int q, int *cursor, int *first) {
    int i;
 if ((*cursor)==(*first)) {
  L[(*cursor)-1]=x;
  (*cursor)--;
  (*first)--;
 } else {
  for (i=(*first);i<(*cursor);i++) L[i-1]=L[i];
  L[(*cursor)-1]=x;
  (*cursor)--;
  (*first)--;
 }
}
void move(long d, int *cursor) {
    (*cursor)+=d;
}
void erase (int *L, int q, int *cursor, int *first) {
    int i;
    for (i=*cursor; i>*first; i--) {
        L[i]=L[i-1];
    }
    (*cursor)++;
    L[(*first)++]=-1;
}
int main (void) {
    int i, q, *L, cursor, query, first;
 long x;
    scanf("%d", &q);
    L=(long *)malloc(sizeof(long)*q+1);
    memset(L, -1, sizeof(long)*q+1);
    cursor=q+1;
    first=q+1;
    for (i=0; i<q; i++) {
        scanf("%d", &query);
        if (query==0) {
            scanf("%d", &x);
            insert (L, x, q, &cursor, &first);
        } else if (query==1) {
            scanf("%d", &x);
            move(x, &cursor);
        } else {
            erase(L, q, &cursor, &first);
        }
  /*
		printf("first:%d cursor:%d\narr:", first, cursor);
		for (j=0;j<q+1;j++) {
	        if (L[j]==-1) continue;
	        printf("%d", L[j]);
			if (i<q+1) printf(" ");
	    }
		printf("\n");
		*/
    }
    for (i=0;i<q+1;i++) {
        if (L[i]==-1) continue;
        printf("%ld\n", L[i]);
    }
    return 0;
}
