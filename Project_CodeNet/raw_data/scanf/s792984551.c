#include <stdio.h>
#define N 100000
int n;
int A[N];
int Partition(int, int);
int main(){
	int i;
	int p=0;
	int r;
	int ans;
	scanf("%d", &n);
	for( i=0; i<n; i++ ){
		scanf("%d", &A[i]);
	}
	r=n-1;
	ans=Partition(p, r);
	for( i=0; i<ans; i++ ) printf("%d ", A[i]);
	printf("[%d] ", A[ans]);
	for( i=ans+1; i<n; i++ ){
		printf("%d", A[i]);
		if( i+1 < n) printf(" ");
	}
	return 0;
}

int Partition(int p, int r){
	int i;
	int j;
	int tmp;
	int x;
	x=A[r];
	i=p-1;
	for( j=p; j<=r-1; j++ ){
		if( A[j] <= x ){
			i++;
			tmp=A[j];
			A[j]=A[i];
			A[i]=tmp;
		}
	}
	tmp=A[r];
	A[r]=A[i+1];
	A[i+1]=tmp;
	return i+1;
}