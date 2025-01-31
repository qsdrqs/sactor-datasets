        #include<stdio.h>
        int main()
        {
            char S[10];
          
            scanf("%s",S);
            
            if(S[0]=='S') printf("Cloudy\n");
            else if(S[0]=='C') printf("Rainy\n");
            else printf("Sunny\n");
          
            return 0;
        }