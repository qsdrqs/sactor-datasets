#include <stdio.h>
#include <stdlib.h>

int main(void){
    long long int x, k, d;
    scanf("%lld %lld %lld", &x, &k, &d);
    int inc=x>0?-1:1;
    for(long long int i=0; i<k; i++){
        if(x>0 && inc==-1){
            x-=d;
            inc=-1;
        }else if(x<=0 && inc==1){
            x+=d;
            inc=1;
        }else{
            if(k%2==0 && i%2==1){
                if(x>0)x-=d;
                else x+=d;
            }else if(k%2==1 && i%2==0){
                if(x>0)x-=d;
                else x+=d;
            }
            break;
        }
    }
    printf("%lld\n", llabs(x));
}
