#include<stdio.h>
int main(){
    int n;scanf("%d",&n);
    int a[100000];
    int sum=0;
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        sum+=a[i]-1;
    }
    printf("%d\n",sum);
    return 0;
}