#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 1000

typedef struct node {
	//データ//
	char command[MAX];
	int number;
	//データ//
	struct node *prev;
	struct node *next;
}node;

int main(void)
{
	char C_input[MAX],//commandに格納する文字列
		instruction[4][12] = { "insert", "delete", "deleteFirst", "deleteLast", };//配列変数commandを単一変数で格納する

	int array[MAX] = { 0 }, a_idx = 0,
		all_number,//入力数
		I_input,//数字
		f_cnt,//ループカウント
		w_cnt,//ループカウント
		dlt_cnt = 0,//deleteした数
		true_cnt = 0;
		

	node *P_node, *fst_node;

	scanf("%d", &all_number);
	
	P_node = malloc(sizeof(node));//最初の構造体を作る


	for (f_cnt = 0; f_cnt < all_number; f_cnt++) {//構造体に双方向連結のためのポインタと、コマンドを入れるループ

		scanf("%s", C_input);

		if (strcmp(C_input, instruction[0]) == 0 || strcmp(C_input, instruction[1]) == 0) {//"insert" or "delete"であった場合
			scanf("%d", &I_input);
		}
		else {
			P_node->number = 0;
		}
		
		w_cnt = 0;
		while (1) {//コマンドを入力
			P_node->command[w_cnt] = C_input[w_cnt];
			if (C_input[w_cnt] == '\0') { break; }
			w_cnt++;
		}

		P_node->number = I_input;//数字を入力
		

		if (f_cnt + 1 == all_number) {//最後の構造体ならNULL
			P_node->next = NULL;
		}
		else {
			P_node->next = malloc(sizeof(node));
		}


		if (f_cnt == 0) {//最初の構造体ならそれ以前の構造体は存在しないのでNULL
			fst_node = P_node;
			P_node->prev = NULL;
		}
		else if (f_cnt + 1 == all_number) { continue; }//最後の構造体なら何も入力しない
		else {
			P_node->next->prev = P_node;//次の構造体のprevに前の構造体（今判定している構造体）のポインタを入れる
		}

		P_node = P_node->next;//次の構造体へ

	}


	P_node = fst_node;//最初の構造体を呼び出す

	for(f_cnt = 0; f_cnt < all_number; f_cnt++){
		
		if(strcmp(P_node->command, instruction[0]) == 0){//先頭に数字を入れる
			array[a_idx] = P_node->number;
			a_idx++;
		}

		else if (strcmp(P_node->command, instruction[1]) == 0) {//指定した数字が配列内にあれば消去してその分詰める
			w_cnt = a_idx;
			while (w_cnt != -1) {//指定した数字が配列に格納されていないかを検索するループ
				if (P_node->number == array[w_cnt]) {

					while (w_cnt != a_idx + 1) {
						array[w_cnt] = array[w_cnt + 1];
						w_cnt++;
					}

					dlt_cnt += 2;
					a_idx--;
					true_cnt = 1;
					break;
				}
				w_cnt--;
			}
			if (true_cnt == 1) {
				true_cnt = 0;
			}
			else {
				dlt_cnt++;
			}
		}

		else if (strcmp(P_node->command, instruction[2]) == 0) {//最後の格納されている数字を消去する
			array[a_idx - 1] = 0;
			dlt_cnt += 2;
			a_idx--;
		}

		else if (strcmp(P_node->command, instruction[3]) == 0) {//最初に格納されている数字を消去してその分詰める
			for (w_cnt = 0; w_cnt < all_number - dlt_cnt; w_cnt++) {
				array[w_cnt] = array[w_cnt + 1];
			}
			dlt_cnt+= 2;
			a_idx--;
		}

		else { break; }

		P_node = P_node->next;//次の構造体へ

	}
	
	w_cnt = f_cnt - dlt_cnt - 1;
	while (w_cnt != -1) {
		printf("%d", array[w_cnt]);
		w_cnt--;
		if (w_cnt != -1) {
			putchar(' ');
		}
	}

	putchar('\n');


	return 0;

}
