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
new->right=NULL;

return new;
}
/*-------------------------------------*/


int main(){
int n,i,x;
char com[13];
node* root;
node* p;
node** q;

root=NULL;

scanf("%d",&n);

for(i=0;i<n;i++){
 scanf("%s",&com);

 if(com[0]=='i'){
   scanf("%d",&x);
   p=makenode(x);
    if(root!=NULL){
        root->left=p;
        p->right=root;
        root=p;
    }else{root=p;}
 }else
 if(strcmp(com,"deleteFirst")==0){
   if(root->right==NULL){root=NULL;}
   else{root->right->left=NULL;
        root=root->right;}
  }else
  if(strcmp(com,"deleteLast")==0){
   if(root->right==NULL){root=NULL;}
   else{q=&(root->right);
    while((*q)!=NULL){
     if((*q)->right==NULL){(*q)=NULL;}
     else{q=&((*q)->right);}
    }
   }
  }else
  if(strcmp(com,"delete")==0){
   scanf("%d",&x);
   if(root->right==NULL){if(root->num==x){root=NULL;}}
   else{q=&(root->right);
    while((*q)!=NULL){
     if((*q)->num==x){
          (*q)->right->left=(*q)->left;
          (*q)=(*q)->right;
          (*q)->right=NULL;
          (*q)->left=NULL;
     }
     else{q=&((*q)->right);}
    }
   }
}
}

p=root;
while(p!=NULL){

if(p->right==NULL){printf("%d\n",p->num);}
else{printf("%d ",p->num);}
p=p->right;

}



return 0;
}




