#include<stdio.h>
#include<stdlib.h>

struct node{
  struct node *right;
  struct node *left;
  struct node *parent;
  int key;
};
typedef struct node * Node;
Node root;
void insert(int k){
  Node y = ((void *)0);
  Node x = root;
  Node z;
  z = malloc(sizeof(struct node));
  z->key = k;
  z->left = ((void *)0);
  z->right = ((void *)0);
  while(x!=((void *)0)){
    y=x;
    if(z->key < x->key){
      x=x->left;
    }
    else x=x->right;
  }
  z->parent=y;
  if(y==((void *)0)) root=z;
  else{
    if(z->key < y->key) y->left = z;
  else y->right = z;
  }
}
void inorder(Node u){
  if(u==((void *)0))return;
  inorder(u->left);
  printf(" %d",u->key);
  inorder(u->right);
}
void preorder(Node u){
  if(u==((void *)0))return;
  printf(" %d",u->key);
  preorder(u->left);
  preorder(u->right);
}
int main(){
  int n, i, x;
  char com[20];
  scanf("%d", &n);
  for ( i = 0; i < n; i++ ){
    scanf("%s", com);
    if ( com[0] == 'i' ){
      scanf("%d", &x);
      insert(x);
    } else if ( com[0] == 'p' ){
      inorder(root);
      printf("\n");
      preorder(root);
      printf("\n");
       }
  }
  return 0;
}
