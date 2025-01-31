#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
char str[] = "KIHBR";
char ret[] = "YES";

if(strcmp(str, argv[1]) != 0){
	strcpy(ret, "NO");
}

printf(ret);

return 0;
}