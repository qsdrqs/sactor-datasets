#include<stdio.h>
#include<stdlib.h>
int main() {
  int a[10000];
    int n,i,q,j,t,p=0,u=0,o=0;
  scanf("%d",&n);
  if(n<1 || 10000<n) exit(0);
  for(i=0;i<n;i++) {
    scanf("%d",&q);
    a[i]=q;
    if(q<2 || 100000000<q) exit(0);

    p=1;
    for(j=2;j<q;j++) {
    t=a[i]%j;
    if(q!=2 && t==0) {p=0; break;}
    }
    if(p==1)
    o++;
  }
    printf("%d\n",o);
    return 0;
  }
  

