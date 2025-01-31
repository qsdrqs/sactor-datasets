//
//  main.c
//  ITP1_5_D
//
//  Created by k16031kk on 2018/05/22.
//  Copyright © 2018年 AIT. All rights reserved.
//

#include <stdio.h>

void call(int n, int c) {
    if(n%10==3) {
        printf(" %d", c);
    }
}
    
int main(int argc, const char * argv[]) {
    // insert code here...
    int n,x,count=0;
    scanf("%d", &n);
    
    for(int i=1; i<=n; i++) {
        x=i;
        count++;
        if(x%3==0) {
            printf(" %d", x);
        } else if(x%10==3) {
            printf(" %d", x);
        } else {
            x/=10;
            call(x,count);
        }
    }
    printf("\n");
    return 0;
}

