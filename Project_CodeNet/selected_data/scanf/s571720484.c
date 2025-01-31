#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

long long powll(long long a,long long b){long long r=1;for(long long i=0;i<(b);i++){r*=a;}return r;}
//      puts(a) printf("%s\n", a) 文字はこっち
//your code here!
int main(void){
    char X[200100];
    scanf("%s", (X));
    //後ろからなめる
    //Sが表れかつ左にTが存在すれば-2
    long long ans=strlen(X), T=0, N=strlen(X);
    for(long long i=0;i<(N);i++){
        if(X[N-1-i]=='T') T++;
        else if(T) ans -= 2;
    }
    printf("%lld\n", (ans));
    return 0;
}
