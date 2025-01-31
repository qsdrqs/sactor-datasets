#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*-----------構造体定義-----------------*/
typedef struct node{
 int num;
 struct node *left;
 struct node *right;
}node;
/*--------------------------------------*/
/*-----------------要素作成-------------*/
node* makenode(int x){
node* new;
new=(node*)malloc(sizeof(node));
new->num=x;
new->right=((void *)0);
return new;
}
/*-------------------------------------*/
int main(){
int n,i,x;
char com[13];
node* root;
node* p;
node** q;
root=((void *)0);
scanf("%d",&n);
for(i=0;i<n;i++){
 scanf("%s",&com);
 if(com[0]=='i'){
   scanf("%d",&x);
   p=makenode(x);
    if(root!=((void *)0)){
        root->left=p;
        p->right=root;
        root=p;
    }else{root=p;}
 }else
 if(strcmp(com,"deleteFirst")==0){
   if(root->right==((void *)0)){root=((void *)0);}
   else{root->right->left=((void *)0);
        root=root->right;}
  }else
  if(strcmp(com,"deleteLast")==0){
   if(root->right==((void *)0)){root=((void *)0);}
   else{q=&(root->right);
    while((*q)!=((void *)0)){
     if((*q)->right==((void *)0)){(*q)=((void *)0);}
     else{q=&((*q)->right);}
    }
   }
  }else
  if(strcmp(com,"delete")==0){
   scanf("%d",&x);
   if(root->right==((void *)0)){if(root->num==x){root=((void *)0);}}
   else{q=&(root->right);
    while((*q)!=((void *)0)){
     if((*q)->num==x){
          (*q)->right->left=(*q)->left;
          (*q)=(*q)->right;
          (*q)->right=((void *)0);
          (*q)->left=((void *)0);
     }
     else{q=&((*q)->right);}
    }
   }
}
}
p=root;
while(p!=((void *)0)){
if(p->right==((void *)0)){printf("%d\n",p->num);}
else{printf("%d ",p->num);}
p=p->right;
}
return 0;
}
