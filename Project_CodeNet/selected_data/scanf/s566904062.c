#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct _treeNode{
  struct _treeNode *right;
  struct _treeNode *left;
  struct _treeNode *parent;
  int key;
}Node;
Node *root;
void insert(int);
void inorder(Node*);
void preorder(Node*);
int main(){
  int command_N;
  int key;
  char command[7];
  scanf("%d",&command_N);
  for(int i=0;i<command_N;i++){
    scanf("%s",command);
    if(strcmp(command,"insert")==0){
      scanf("%d",&key);
      insert(key);
    }
    else if(strcmp(command,"print")==0){
      inorder(root);
      printf("\n");
      preorder(root);
      printf("\n");
    }
  }
return 0;
}
void insert(int key){
  Node *in;
  Node *current=root;
  Node *pre=((void *)0);
  in=(Node*)malloc(sizeof(Node));
  in->key=key;
  in->left=((void *)0);
  in->right=((void *)0);
  while(current!=((void *)0)){
    pre=current;
    if(in->key<current->key){
      current=current->left;
    }
    else{
      current=current->right;
    }
  }
  in->parent=pre;
  if(pre==((void *)0)){ //空
    root=in;
  }else{
    if(in->key<pre->key){
      pre->left=in;
    }else{
      pre->right=in;
    }
  }
}
void inorder(Node *node){
  if(node==((void *)0)) return;
  inorder(node->left);
  printf(" %d",node->key);
  inorder(node->right);
}
void preorder(Node *node){
  if(node==((void *)0)) return;
  printf(" %d",node->key);
  preorder(node->left);
  preorder(node->right);
}
