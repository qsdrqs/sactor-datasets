#include<stdio.h>
int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    if(a>b){
        for(int i=0;i<a;i++){
            printf("%d",b);
        }
    }
    else if(a<b){
        for(int j=0;j<b;j++){
            printf("%d",a);
        }
    }
    else {
        for(int k=0;k<b;k++){
            printf("%d",a);
        }
    }
}