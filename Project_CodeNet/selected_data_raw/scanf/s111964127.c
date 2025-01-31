#include <stdio.h>
int main(void){
    long int N,M,i,cnt=0;
    long int H[100001];
    long int A[100000];
    long int B[100000];
    long int Nflag[100001];
    
    scanf("%ld",&N);
    scanf("%ld",&M);
    for(i=1;i<=N;i++){
        scanf("%ld",&H[i]);
        Nflag[i]=1;
    }
    
    for(i=0;i<M;i++){
        scanf("%ld",&A[i]);
        scanf("%ld",&B[i]);
        
        if(H[A[i]]<H[B[i]]){
            Nflag[A[i]]=0;
        }else if(H[A[i]]>H[B[i]]){
            Nflag[B[i]]=0;
        }else if(H[A[i]]==H[B[i]]){
            Nflag[A[i]]=0;
            Nflag[B[i]]=0;
        }
        
    }
    
    for(i=1;i<=N;i++){
        if(Nflag[i]==1){
            cnt++;
        }
    }
    
    printf("%ld\n",cnt);
    
    return 0;
}