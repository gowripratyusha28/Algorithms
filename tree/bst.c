#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int key;
	struct node *left;
	struct node *right;
	struct node *parent;
}NODE;

NODE *create(int n){
	NODE *new;
	new=(NODE *)malloc(sizeof(NODE));
	new->key=n;
	new->left=NULL;
	new->right=NULL;
	new->parent=NULL;
	return new;
}

NODE *insert(NODE *head,int n){
	NODE *newnode=create(n);
	NODE *temp=head;
	if(head==NULL) return newnode;
	else{
		while(1){
			if(newnode->key<temp->key){
				if(temp->left==NULL){
					temp->left=newnode;
					newnode->parent=temp;                    //INSERT AN ELEMENT
					break;
				}
				temp=temp->left;
			}
			else{
				if(temp->right==NULL){
					temp->right=newnode;
					newnode->parent=temp;
					break;
				}
				temp=temp->right;
			}
		}
	return head;
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
		printf("%d ",temp->key);
		inorder(temp->right);
	}
}

NODE *search(NODE *head,int k){
	NODE *temp=head;
	if(temp==NULL) return NULL;
	if(temp->key==k) return temp;
	if(temp->key<k) return search(temp->right,k);            //SEARCH AN ELEMENT
	if(temp->key>k) return search(temp->left,k); 
}

NODE *min(NODE *head){
	NODE *temp=head;
	while(temp->left!=NULL){                                 //MIN OF TREE
		temp=temp->left;
	}
	return temp;
}

NODE *max(NODE *head){
	NODE *temp=head;
	while(temp->right!=NULL){
		temp=temp->right;                                    //MAX OF TREE 
	}
	return temp;
}

NODE *successor(NODE *root,NODE *n){
	if(n->right!=NULL) {
		return min(n->right);
	}
	NODE *p=n->parent;                                      
	while(p!=NULL && n==p->right){
		n=p;
		p=p->parent;
	}
	return p;
}

struct node *deleteNode(struct node *root,int k){
	if(root==NULL) return root;
	if(k<root->key) root->left=deleteNode(root->left,k);
	else if(k>root->key) root->right=deleteNode(root->right,k);
	else{
		if(root->left==NULL){
			NODE *temp=root->right;                                    //DELETE AN ELEMENT
			free(root);
			return temp;
		}
		else if(root->right==NULL){
			NODE *temp=root->left;
			free(root);
			return temp;
		}
		else{
			NODE *temp=min(root->right);
			root->key=temp->key;
			root->right=deleteNode(root->right,temp->key);
		}
	}
	return root;
}

NODE *constructTree(int *arr,int *index,int low,int high,int size){
	if(*index>size ||low>high) return NULL;
	NODE *root=create(arr[*index]);
	*index=*index+1;
	if(high==low) return root;
	int i;
	for(i=low;i<=high;i++){
		if(arr[i]>root->key) break;
	}
	root->left=constructTree(arr,index,*index,i-1,size);
	root->right=constructTree(arr,index,i,high,size);
	return root;
}

NODE *construct(int *arr,int size){
	int index=0;
	constructTree(arr,&index,0,size-1,size);
}

int main(){
	NODE *head=NULL,*t=NULL,*s=NULL;
	int v,a,i,b,c;
	printf("Enter number of nodes: ");
	scanf(" %d",&v);
	int *arr;
	arr=(int *)malloc(v*sizeof(int));
	for(i=0;i<v;i++){
		printf("Enter: ");
		scanf(" %d",&arr[i]);
	}
	head=construct(arr,v);
	printf("Preorder: ");
	preorder(head);
	printf("\n");
	// printf("Enter number whose successor is needed: ");
	// scanf(" %d",&b);
	// t=search(head,b);
	// if(t!=NULL){
	// 	printf("Found %d\n",t->key);
	// 	//printf("Parent is %d\n",t->parent->key);
	// }
	// else printf("Not found\n");
	// s=successor(head,t);
	// printf("Successor of %d is %d\n",b,s->key);
	printf("Inorder: ");
	inorder(head);
	printf("\n");
	printf("Enter number to delete: ");
	scanf(" %d",&c);
	head=deleteNode(head,c);
	printf("Preorder: ");
	preorder(head);
	printf("\n");
	printf("Enter number to delete: ");
	scanf(" %d",&c);
	head=deleteNode(head,c);
	printf("Preorder: ");
	preorder(head);
	printf("\n");
	printf("Enter number to delete: ");
	scanf(" %d",&c);
	head=deleteNode(head,c);
	printf("Preorder: ");
	preorder(head);
	printf("\n");
	s=min(head);
	printf("Minimum element: %d",s->key);
	printf("\n");
	t=max(head);
	printf("Maximum element: %d",t->key);
	printf("\n");
}