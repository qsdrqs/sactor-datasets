
#include <stdio.h>

void dis(int *arr,int n)
{
    for(int i = 0;i<n;i++)
    {
        if(i>0)
            printf(" ");
        printf("%d",arr[i]);
    }
    printf("\n");
}

int BubbleSort(int * arr,int n)
{
    int Num = 0;
    for(int i = 0;i<n;i++)
        for(int j = n-1;j>i;j--)
        {
            if(arr[j-1]>arr[j])
            {
                arr[j-1] ^= arr[j];
                arr[j] ^= arr[j-1];
                arr[j-1] ^= arr[j];
                Num++;
            }
    }
    return Num;
}



int main(int argc, char *argv[])
{
    int N;
    int A[100];

    scanf("%d",&N);
    for(int i = 0;i<N;i++)
    {
        scanf("%d",&A[i]);
    }
    int num = BubbleSort(A,N);
    dis(A,N);
    printf("%d\n",num);
    return 0;
}

