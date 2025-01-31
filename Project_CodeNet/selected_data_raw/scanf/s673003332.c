#include <stdio.h>
#define rep(i,n) for(int i=0;i<n;i++)
typedef long long ll;

int main()
{
    ll ans=1;
    int march[5]={0};
    int n,sum=0,el=0;
    scanf("%d",&n);
    char s[15];
    rep(i,n){
        scanf("%s",s);
        switch(s[0]){
            case 'M': march[0]++; break;
            case 'A': march[1]++; break;
            case 'R': march[2]++; break;
            case 'C': march[3]++; break;
            case 'H': march[4]++; break;
            default : break;
        }
    }
    
    for(int i=0;i<3;i++){
        for(int j=i+1;j<4;j++){
            for(int k=j+1;k<5;k++){
                ans+=march[i]*march[j]*march[k];
            }
        }
    }
    printf("%lld",ans);
}
