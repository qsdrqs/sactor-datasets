//tree DP
//ABC036-D
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#define inf 1072114514
#define llinf 4154118101919364364
#define mod 1000000007
#define pi 3.1415926535897932384

long long llmax(long long a,long long b){if(a>b){return a;}return b;}
long long llmin(long long a,long long b){if(a<b){return a;}return b;}
long long llzt(long long a,long long b){return llmax(a,b)-llmin(a,b);}

typedef struct{
int val;
int node;
}sd;

int sdsortfnc(const void *a,const void *b){
if(((sd*)a)->val > ((sd*)b)->val){return -1;}
if(((sd*)a)->val < ((sd*)b)->val){return 1;}
return 0;
}

typedef struct{
    long long st;
    long long fi;
    long long kr;
}rs;

typedef struct{
    long long st;
    long long kz;
}mkj;

int sortfnc(const void *a,const void *b){
if(((rs*)a)->st == ((rs*)b)->st){return 0;}
if(((rs*)a)->st < ((rs*)b)->st){return -1;}
return 1;
}

void makemkj(rs g[],mkj x[],long long n){
    long long i,ms=0,nst=g[0].st;
    for(i=1;i<n;i++){
        if(g[i].st!=g[i-1].st){
            x[nst].kz=i-ms;
            x[nst].st=ms;
            nst=g[i].st;ms=i;
        }
    }
    x[nst].kz=n-ms;
    x[nst].st=ms;
}

long long dist[524288],par[524288];
void dfs(long long t,long long l,long long bp,rs g[],mkj x[]){
  long long i;
  if(dist[t]<=l){return;}
  dist[t]=l;
  par[t]=bp;
  for(i=x[t].st;i<x[t].st+x[t].kz;i++){
    dfs(g[i].fi,l+1,t,g,x);
  }
}

int main(void){
    long long i,j,n,m,k,a,b,c,h,w,r,l,t,f;
    long long bk,wk;
    long long res=0;
    long long ds[524288],dw[524288];
    char s[524288];
    rs g[524288];
    mkj x[524288];
    sd dat[524288];
    scanf("%lld%s",&n,&s[1]);
    for(i=0;i<(n-1);i++){
      scanf("%lld%lld",&a,&b);
      g[2*i].st=a;
      g[2*i].fi=b;
      g[2*i].kr=1;
      g[2*i+1].st=b;
      g[2*i+1].fi=a;
      g[2*i+1].kr=1;
    }
    qsort(g,2*(n-1),sizeof(g[0]),sortfnc);
    makemkj(g,x,2*(n-1));
    r=llinf;
    for(t=1;t<=n;t++){
      for(i=0;i<=n;i++){
        dist[i]=inf;
        ds[i]=0;
        dw[i]=0;
      }
      dfs(t,0,-1,g,x);
      for(i=0;i<n;i++){
        dat[i].node=i+1;
        dat[i].val=dist[i+1];
      }
      qsort(dat,n,sizeof(dat[0]),sdsortfnc);
      for(i=0;i<n;i++){
        w=dat[i].node;
        if(s[w]=='1'){dw[w]++;}
        for(j=x[w].st;j<x[w].st+x[w].kz;j++){
          if(par[w]==g[j].fi){continue;}
          dw[w]+=dw[g[j].fi];
          ds[w]+=(dw[g[j].fi]+ds[g[j].fi]);
        }
        //printf("%lld %lld : %lld %lld\n",t,w,dw[w],ds[w]);
      }
      if(ds[w]%2==1){continue;}
      w=t;f=1;a=ds[w]/2;
      while(x[w].kz!=1){
        for(j=x[w].st;j<x[w].st+x[w].kz;j++){
          if(par[w]==g[j].fi){continue;}
          if((ds[w]-a) < (dw[g[j].fi]+ds[g[j].fi])){
            f=0;
            a-=(ds[w]- (dw[g[j].fi]+ds[g[j].fi]));
            w=g[j].fi;
            break;
          }
        }
        if(f==1){r=llmin(ds[t]/2,r);break;}
      }
    }
    if(r==llinf){r=-1;}
    printf("%lld\n",r);
    return 0;
}
