#include<stdio.h>
#include<string.h>

int main(void){
    
    int N,i;
    char S[10002],alpha_num;

    scanf("%d",&N);
    scanf("%s",S);

    for(i = 0;i < strlen(S);i++){
        alpha_num = S[i] + (char)N;
        if(alpha_num > 'Z'){
            alpha_num -= 26;
        }
        printf("%c",alpha_num);
    }

    printf("\n");
    return 0;
}
