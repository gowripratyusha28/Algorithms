#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
	struct node *parent;
}NODE;

NODE *create(int n){
	NODE *newnode;
	newnode=(NODE *)malloc(sizeof(NODE));
	newnode->key=n;
	newnode->left=NULL;
	newnode->right=NULL;
	newnode->parent=NULL;
	return newnode;
}

void insert(NODE *head,int a){
	NODE *newnode;
	newnode=create(a);
		while(1){
			if(newnode->key<head->key){
				if(head->left==NULL){
					head->left=newnode;
					newnode->parent=head;
					break;
				}
				head=head->left;
			}
			else{
				if(head->right==NULL){
					head->right=newnode;
					newnode->parent=head;
					break;
				}
			head=head->right;
		}
	}
}

void preorder(NODE *head){
	NODE *temp=head;
	if(temp!=NULL){
		printf("%d  ",temp->key);
		preorder(temp->left);
		preorder(temp->right);
	}
}

void inorder(NODE *head){
	NODE *temp=head;
	if(temp!=NULL){
		inorder(temp->left);
		printf("%d  ",temp->key);
		inorder(temp->right);
	}
}

void postorder(NODE *head){
	NODE *temp=head;
	if(temp!=NULL){
		postorder(temp->left);
		postorder(temp->right);
		printf("%d  ",temp->key);
	}
}

int main(){
	NODE *head=NULL;
	int v,i,a;
	printf("Enter number of nodes: ");
	scanf(" %d",&v);
	printf("Enter data: ");
	scanf(" %d",&a);
	head=create(a);
	for(i=0;i<v-1;i++){
		printf("Enter data: ");
		scanf(" %d",&a);
		insert(head,a);
	}
	printf("Preorder: ");
	preorder(head);
	printf("\n");
	printf("Inorder: ");
	inorder(head);
	printf("\n");
	printf("Postorder: ");
	postorder(head);
	printf("\n");
}	