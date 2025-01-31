#include <stdio.h>
int main(void){
    char s[100000];
    int i,count,n,q,st,gt,j,last,fast,mode;
    count = i = j = last = fast = mode = 0;
    scanf("%d",&n);
    scanf("%d",&q);
    scanf("%s",s);
    while(1){
        if (s[i] == '\0'){
            break;
        }else if (s[i] == 'A'){
            if (s[i+1] == 'C'){
                if (mode == 0){
                    fast = i;
                    mode = 1;
                }
                last = i;
            }
        }
        i++;
    }
    for(j = 0; j < q; j++){
        scanf("%d",&st);
        scanf("%d",&gt);
        st = st - 1;
        gt = gt - 1;
        if (last < st){
            printf("%d\n",count); 
            continue;
        }
        if (fast > st){
            st = fast;
        }
        for(i = st; i < gt; i++){
            if (s[i] == 'A'){
                if (s[i+1] == 'C'){
                    count++;
                    i++;
                }
            }
        }
        printf("%d\n",count); 
        count = 0;
    }
}