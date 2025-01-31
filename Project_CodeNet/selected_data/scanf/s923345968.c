#include<stdio.h>

int cnt;
void merge(int *, int ,int ,int);
void mergeSort(int *,int, int);
int main(){
    int a,A[100000],i;
    scanf("%d",&a);
    for(i = 0;i < a;i++){
        scanf("%d",&A[i]);
    }
    mergeSort(A,0,a);
    for(i = 0;i < a;i++){
        if(i == a - 1){
            printf("%d\n",A[i]);
        }else printf("%d ",A[i]);
    }
    printf("%d\n",cnt);
    return 0;
}
void merge(int *A,int left,int mid,int right)
{
int n1,n2;
int i,j,k;
n1 = mid - left;
n2 = right - mid;
int L[n1 + 1],R[n2 + 1];
for(i = 0;i < n1;i++){
    L[i] = A[left + i];
}
for(i = 0;i < n2;i++){
    R[i] = A[mid + i];
}
L[n1] = 100000;
R[n2] = 100000;
i = 0;
j = 0;
for(k = left;k < right;k++){
    if(L[i] <= R[j]){
        A[k] = L[i];
        i++;
        cnt++;
    }else{
        A[k] = R[j];
        j++;
        cnt++;
    }
  }
}
void mergeSort(int *A,int left,int right){
    int mid;
    if(left+1 < right){
    mid = (left + right) / 2;
    mergeSort(A, left, mid);
    mergeSort(A, mid,right);
    merge(A,left,mid,right);
    }
}
