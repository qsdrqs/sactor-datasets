#include<stdio.h>

int R=1,C=1,H[2000020],N[2000020];
int hyouka(int a,int b){
  if(C<b)return 1;
  if(C<a||b==0)return 0;
  return N[H[a]]<N[H[b]]?1:0;
}
void hin(int a){
  int i=C++;
  for(N[H[0]=R]=a;hyouka(0,i/2);i/=2)H[i]=H[i/2];
  H[i]=R++;
}
int hout(){
  int rt=H[1],i,j=2,k=H[--C];
  for(i=1;hyouka(i,C);i=j)H[j=i*2+1-hyouka(i*2,i*2+1)];
  H[j/2]=k;
  return rt;
}
int CO[100010];
void dijk(int v,int e,int *fr,int *to,int *co,int mi){
  int i,id[100010],ta[100010],nt[200010],f[100010]={0};
  for(i=1;i<=v;i++)ta[i]=-1;
  for(i=1;i<v;i++)CO[i]=1e9+1e8;
  for(i=CO[mi]=0;i<e;i++){
    if(fr[i]==v)continue;
    nt[i]=ta[fr[i]];
    ta[fr[i]]=i;
  }
  while(f[mi]-1){
    f[mi]=1;
    for(i=ta[mi];i+1;i=nt[i]){
      if(CO[mi]>co[i])continue;
      if(CO[to[i]]>co[i])hin(CO[id[R]=to[i]]=co[i]);
    }
    while(f[mi]&&C-1)mi=id[hout()];
  }
}
int main(){
  int i,max,n,m,a[200010],b[200010],c[200010];
  scanf("%d %d",&n,&m);
  for(i=0;i<m;i++)scanf("%d %d %d",&a[i],&b[i],&c[i]);
  dijk(n,m,a,b,c,1);
  max=-1;
  for(i=0;i<m;i++){//printf("%d %d\n",i,CO[i]);
    if(b[i]-n||CO[a[i]]>c[i])continue;
    if(max<c[i])max=c[i];
  }
  printf("%d\n",max);
  return 0;
}
