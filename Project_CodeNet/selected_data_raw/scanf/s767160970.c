#include<stdio.h>

int main(){
    int n, m;
    long int k;
    scanf("%d%d%ld", &n, &m, &k);
    long int a[n], b[m];
    for(int i = 0; i < n; i++){
        scanf("%ld", &a[i]);
    }
    
    for(int i = 0; i < m; i++){
        scanf("%ld", &b[i]);
    }
    long int minute = 0, ans = 0;
    int i =0, j = 0;
    while(minute <= k){
        if(a[i] <= b[j]){
            minute = minute + a[i];
            i++;
        }
        else if(a[i] > b[j]){
            minute = minute + b[j];
            j++;
        }    
        if(minute <= k){
            ans++;
        } 
        if(i == n && j == m){break;}
        
        
    }
    printf("%ld", ans);
    return 0;
}    
