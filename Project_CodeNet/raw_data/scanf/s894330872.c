#include <stdio.h>

typedef struct Card{
	char suit,value;
}Card;

void selectionSort(Card *,int);
void bubbleSort(Card *,int);
int isStable(Card *,Card *,int);
void printData(Card *,int);

int main(void){
	int i,n;
	Card c1[36],c2[36];
	char S[3];
	
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%s",S);
		c1[i].suit=S[0];
		c1[i].value=S[1];
	}
	for(i=0;i<n;i++){
		c2[i]=c1[i];
	}
	
	bubbleSort(c1,n);
	printData(c1,n);
	printf("Stable\n");
	selectionSort(c2,n);
	printData(c2,n);
	if(isStable(c1,c2,n)){
		printf("Stable\n");
	}
	else{
		printf("Not stable\n");
	}
	
	return 0;
}

void selectionSort(Card *c,int n){
	int i,j;
	int minj;
	
	for(i=0;i<n;i++){
		minj=i;
		for(j=i;j<n;j++){
			if(c[j].value<c[minj].value)
				minj=j;
		}
		if(c[i].value!=c[minj].value){
			Card t=c[i];
			c[i]=c[minj];
			c[minj]=t;
		}
	}
}

void bubbleSort(Card *c,int n){
	int i;
	int flag=1;
	while(flag){
		flag=0;
		for(i=n-1;i>0;i--){
			if(c[i].value<c[i-1].value){
				Card t=c[i];
				c[i]=c[i-1];
				c[i-1]=t;
				flag=1;
			}
		}
	}
}

int isStable(Card *c1,Card *c2,int n){
	int i;
	
	for(i=0;i<n;i++){
		if(c1[i].suit!=c2[i].suit){
			return 0;
		}
	}
	
	return 1;
}

void printData(Card *c,int n){
	int i;
	for(i=0;i<n;i++){
		printf("%c%c",c[i].suit,c[i].value);
		if(i<n-1)
			printf(" ");
	}
	printf("\n");
}