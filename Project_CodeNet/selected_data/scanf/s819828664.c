#include<stdio.h>

int main(void){
 int cnt,n;
 unsigned int i,w,h[101],sa[5];
 while(scanf("%d",&n),n!=0){
  for(i=0;i<=n;i++)scanf("%d",&h[i]);
  sa[0]=h[1]-h[0];
  sa[1]=h[i-1]-h[i-2];
  sa[2]=h[(i-1)/2]-h[(i-1)/2-1];
  sa[3]=h[(i-1)/2+1]-h[(i-1)/2];
  if(sa[0]==sa[1] || sa[1]==sa[2] || sa[1]==sa[3])sa[4]=sa[1];
  if(sa[0]==sa[2] || sa[0]==sa[3])sa[4]=sa[0];
  for(i=1;i<=n;i++){
   if(h[i]-h[i-1]!=sa[4]){
    cnt++;
    if(cnt>1)w=h[i-1];
    if(h[i+1]-h[i]==sa[4])w=h[i-1];
    if(i==n && w<1)w=h[i];
   }
  }
  printf("%d\n",w);
  cnt=w=0;
 }
 return 0;
}
