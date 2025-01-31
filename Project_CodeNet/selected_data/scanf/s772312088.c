#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long cycles[5001][5001]={0},nofcycles=0,cyclescore[5001]={0},used[5000]={0},lenofcycles[5001]={0};
int main(int argv,char* argc[]){
    long long n,k;
    scanf("%lld%lld",&n,&k);
    long long c[n];
    long long p[n];
    for(int i=0;i<n;i++){
        scanf("%lld",&p[i]);
        p[i]--;
    }
    for(int i=0;i<n;i++){
        scanf("%lld",&c[i]);
    }
    for(int i=0;i<n;i++){
        if(used[i]==1){
            continue;
        }
        int z=0;
        long long tmp=i;
        while(used[tmp]==0){
            used[tmp]=1;
            cycles[nofcycles][z]=tmp;
            z++;
            cyclescore[nofcycles]+=c[tmp];
            tmp=p[tmp];
        }
        lenofcycles[nofcycles]=z;
        nofcycles++;
    }
    long long ans=-11451419198100000;
    for(int i=0;i<nofcycles;i++){
        long long tmp=0,res=k;
        if(cyclescore[i]>=0){
            tmp+=cyclescore[i]*(k/lenofcycles[i]);
            res=k%lenofcycles[i];
            for(int j=0;j<lenofcycles[i];j++){
                long long x=0;
                long long pos=cycles[i][j];
                for(int h=0;h<res;h++){
                    x+=c[pos];
                    pos=p[pos];
                }
                if(ans<x+tmp){
                    ans=x+tmp;
                }
            }
        }else{
            for(int j=0;j<lenofcycles[i];j++){
                long long pos=cycles[i][j];
                long long x=0,max=-11451419198100000;
                for(int h=0;h<lenofcycles[i]&&h<k;h++){
                    x+=c[pos];
                    pos=p[pos];
                    max=max<x?x:max;
                }
                if(ans<tmp+max){
                    ans=tmp+max;
                }
            }
        }
    }
    printf("%lld",ans);
    return 0;
}
