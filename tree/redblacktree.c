#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	char colour;
	struct node *left,*right,*p;
};

struct node *newnode(int key){
	struct node *temp=(struct node *)malloc(sizeof(struct node));
	temp->data=key;
	temp->right=NULL;
	temp->left=NULL;
	temp->p=NULL;
	temp->char='R';
	return temp;
}

void leftrotate(struct node **root,struct node *x){
	struct node *y=x->right;
	x->right=y->left;
	if(y->left!=NULL){
		y->left->p=x;
	}
	y->p=x->p;
	if(x->p==NULL){
		root=y;
	}
	else if(x==x->p->left){
		x->p->left=y;
	}
	else{
		x->p->right=y;
	}
	y->left=x;
	x->p=y;
}

void rightrotate(struct node **root,struct node *x){
	struct node *x=y->left;
	x->left=y->right;
	if(x->right!=NULL){
		x->right->p=y;
	}
	x->p=x->p;
	if(y->p==NULL){
		root=x;
	}
	else if(y==y->p->left){
		y->p->left=x;
	}
	else{
		y->p->left=x;
	}
	x->right=y;
	y->p=x;
}

void insertfixup(struct node **root,struct node *z){
	struct node *y;
	while(z->p->colour=='R'){
		if(z->p==z->p->p->left){
			y=z->p->p->right;
			if(y->colour=='R'){
				z->p->colour='B';
				y->colour='B';
				z->p->p->colour='R';
				z=z->p->p;
			}
			else if(z==z->p->right){
				z=z->p;
				leftrotate(root,z);
			}
			z->p->colour='B';
			z->p->p->colour='R';
			rightrotate(root,z->p->p);
		}
		else{
			y=z->p->p->left;
			if(y->colour=='R'){
				z->p->colour='B';
				y->colour='B';
				z->p->p->colour='R';
				z=z->p->p;
			}
			else if(z==z->p->left){
				z=z->p;
				rightrotate(root,z);
			}
			z->p->colour='B';
			z->p->p->colour='R';
			leftrotate(root,z->p->p);
		}
	}
	root->colour='B';
}

void insert(struct node **root,int key){
	struct node *z=newnode(key);
	struct node *y=NULL;
	struct node *x=*root;
	while(x!=NULL){
		y=x;
		if(z->data<x-data){
			x=x->left;
		}
		else x=x->right;
	} 
	z->p=y;
	if(y==NULL){
		*root=z;
	}
	else if(z->data<y->data){
		y->left=z;
	}
	else y->right=z;
	z->left=NULL;
	z->right=NULL;
	z->colour='R';
	insertfixup(root,z);
}

void preorder(struct node *root){
	struct node *temp=root;
	if(temp!=NULL){
		printf("%d",temp->data);
		preorder(temp->left);
		preorder(temp->right);
	}
}

int main(){
	int n,i,a;
	struct node *head=NULL;
	head=insert(&root,7);
	head=insert(&root,6);
	head=insert(&root,5);
	head=insert(&root,4);
	head=insert(&root,3);
	head=insert(&root,2);
	head=insert(&root,1);
	preorder(head);
}