#include <stdlib.h>
#include <stdio.h>
int compare(const void *a,const void *b){
    if(*(long *)a>*(long *)b)return -1;
    return 1;
}
int main()
{   
    long n,h;
    scanf("%ld%ld",&n,&h);
    long a[n],b[n];
    for(int i=0;i<n;i++){
        scanf("%ld%ld",&a[i],&b[i]);
    }
    qsort(a,n,sizeof(long),compare);
    qsort(b,n,sizeof(long),compare);
    
    
    long ans=0,i=0;
    while(h>0){
        
        if(a[0]>b[i]||i==n){
            if(h%a[0]==0){
            ans+=h/a[0];}
            else{
                ans+=h/a[0]+1;
            }
            break;
        }else{
            h-=b[i];
            i++;
            ans++;
        }
    }
    printf("%ld",ans);

    return 0;
}
