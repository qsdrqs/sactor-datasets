#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef long long ll; typedef long double ld;
typedef struct node { int data; struct node *next; } Node;
Node *list[100005];
int queue[100005]; int q_head = 0, q_tail = 0;
void print_log(); //とりあえず文字を出力してどこまで実行できているか確認(for debug)
void printa_int(int *a, int size); //int型の1次元配列aを出力(for debug)
void printl_int(int size); //リンクリストを出力(for debug)
Node* add_node(int i, int data); void free_list(Node* head);
int queue_empty(); int queue_full();
void enqueue(int data); int dequeue();
int main() {
    ll A, res;
    double B;
    scanf("%lld %lf", &A, &B);
    res = A * (int)(B * 100 + 0.5) / 100;
    printf("%lld\n", res);
    return 0;
}
void print_log() {
    printf("=== print log ===\n");
}
void printa_int(int *a, int size) {
    int i;
    printf("[");
    for (i = 0; i < size; i++)
        printf("%d, ", a[i]);
    printf("]\n");
}
void printl_int(int size) {
    int i;
    Node *t;
    for (i = 0; i < size; i++) {
        printf("[%d] ", i);
        for (t = list[i]; t; t = t->next) printf("%d, ", t->data);
        printf("\n");
    }
}
Node* add_node(int i, int data) {
    if (!list[i]) {
        list[i] = (Node*)malloc(sizeof(Node*));
        list[i]->data = data;
    } else {
        Node *t;
        t = list[i];
        list[i] = (Node*)malloc(sizeof(Node*));
        list[i]->data = data;
        list[i]->next = t;
    }
    return list[i];
}
void free_list(Node* head) {
    Node *prev = ((void *)0), *t = head;
    while (t) {
        prev = t;
        t = t->next;
        free(prev);
    }
}
int queue_empty() {
    return q_head == q_tail;
}
int queue_full() {
    return (q_head - 1) % 100005 == q_tail % 100005;
}
void enqueue(int data) {
    if (queue_full()) {
        printf("full!\n");
        return;
    }
    queue[q_tail++] = data;
    q_tail %= 100005;
}
int dequeue() {
    if (queue_empty()) {
        printf("empty!\n");
        return -444444;
    }
    int data = queue[q_head++];
    q_head %= 100005;
    return data;
}
