#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	char *letter;
	int length;
	int i, n;
	letter = argv[1];
	printf("%s\n", argv[1]);
	
	// 文字数を調べる
	for(i=0; i<=21; i++){
		printf("%c", letter[i]);
		if(letter[i] == '\0'){
			i -= 1;
			break;
		}
	}
	//
	for(n=i; n>=0; n--){
		printf("%c", letter[n]);
		i+1;
	}
	return 0;
}