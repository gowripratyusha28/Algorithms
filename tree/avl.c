#include <stdio.h>
#include <stdlib.h>

struct node{
	int key;
	struct node *left,*right;
	int height;
};

int height(struct node *a){
	int lh,rh;
	if(a==NULL) return 0;
	if(a->left==NULL) lh=0;
	else lh=1+a->left->height;
	if(a->right==NULL) rh=0;
	else rh=1+a->right->height;
	if(lh>rh) return lh;
	else return rh;
}

struct node *newnode(int k){
	struct node *new;
	new=(struct node *)malloc(sizeof(struct node));
	new->key=k;
	new->left=NULL;
	new->right=NULL;
}

struct node *rotateright(struct node *x){
	struct node *y=x->left;
	x->left=y->right;
	y->right=x;
	y->height=height(y);
	x->height=height(x);
	return y;
}

struct node *rotateleft(struct node *x){
	struct node *y=x->right;
	x->right=y->left;
	y->left=x;
	y->height=height(y);
	x->height=height(x);
	return y;
}

int balancefactor(struct node *T){
	int lh,rh;
	if(T==NULL)
		return(0);
 
	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->height;
 
	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->height;
 
	return(rh-lh);
}

struct node *min(struct node *head){
	struct node *temp=head;
	while(temp->left!=NULL){                                
		temp=temp->left;
	}
	return temp;
}

/*struct node *insert(struct node *root,int k){
	if(root==NULL){
		root=(struct node*)malloc(sizeof(struct node));
		root->key=k;
		root->left=NULL;
		root->right=NULL;
	}
	else{
		if(k>root->key){
			root->right=insert(root->right,k);
			if(balancefactor(root)==2){
				if(k>root->right->key){
					return rotateleft(root);
				}
				else{
					root->right=rotateright(root->right);
					return rotateleft(root);
				}
			}
		}
		if(k<root->key){
			root->left=insert(root->left,k);
			if(balancefactor(root)==-2){
				if(k<root->left->key){
					return rotateright(root);
				}
				else{
					root->left=rotateleft(root->left);
					return rotateright(root);
				}
			}
		}
		root->height=height(root);
	}
	return root;
}*/

struct node* insert(struct node* node, int key) 
{ 
    /* 1.  Perform the normal BST rotation */
    if (node == NULL) 
        return(newnode(key)); 
  
    if (key < node->key) 
        node->left  = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key); 
    else // Equal keys not allowed 
        return node; 
  
    /* 2. Update height of this ancestor node */
    node->height = height(node); 
  
    int balance = balancefactor(node); 
    if (balance > 1 && key < node->left->key) 
        return rotateright(node); 
  
    // Right Right Case 
    if (balance < -1 && key > node->right->key) 
        return rotateleft(node); 
  
    // Left Right Case 
    if (balance > 1 && key > node->left->key) 
    { 
        node->left =  rotateleft(node->left); 
        return rotateright(node); 
    } 
  
    // Right Left Case 
    if (balance < -1 && key < node->right->key) 
    { 
        node->right = rotateright(node->right); 
        return rotateleft(node); 
    } 
  
    /* return the (unchanged) node pointer */
    return node; 
}

struct node *delete(struct node *root,int k){
	if(root==NULL) return root;
	if(k<root->key){
		root->left=delete(root->left,k);
		if(balancefactor(root)==2){
			if(balancefactor(root->left)>=0){
				return rotateleft(root);
			}
			else{
				root->right=rotateright(root->right);
				return rotateleft(root);
			}
		}
	}
	else if(k>root->key){
		root->right=delete(root->right,k);
		if(balancefactor(root)==-2){
			if(balancefactor(root->right)<=0){
				return rotateright(root);
			}
			else{
				root->left=rotateleft(root->left);
				return rotateright(root);
			}
		}
	}
	else{
		if(root->right!=NULL){
			struct node *temp=min(root->right);
			root->key=temp->key;
			root->right=delete(root->right,temp->key);
			if(balancefactor(root)==-2){
				if(balancefactor(root->left)<=0){
					return rotateright(root);
				}
				else{
					root->left=rotateleft(root->left);
					return rotateright(root);
				}
			}
		}
		else return root->left;
	}
	root->height=height(root);
	return(root);
}

void preorder(struct node *head){
	struct node *temp=head;
	if(temp!=NULL){
		printf("%d(bf==%d)  ",temp->key,balancefactor(temp));    
		preorder(temp->left);
		preorder(temp->right);
	}
}

int main(){
	struct node *head=NULL;
	head=insert(head,9);
	printf("Preorder:\n");
	preorder(head);
	printf("\n");
	head=insert(head,5);
	printf("Preorder:\n");
	preorder(head);
	printf("\n");
	head=insert(head,10);
	printf("Preorder:\n");
	preorder(head);
	printf("\n");
	head=insert(head,0);
	printf("Preorder:\n");
	preorder(head);
	printf("\n");
	head=insert(head,6);
	printf("Preorder:\n");           
	preorder(head);
	printf("\n");
	head=insert(head,11);
	printf("Preorder:\n");
	preorder(head);
	printf("\n");
	head=insert(head,-1);
	printf("Preorder:\n");
	preorder(head);
	printf("\n");
	head=insert(head,1);
	printf("Preorder:\n");
	preorder(head);
	printf("\n");
	head=insert(head,2);
	printf("Preorder:\n");
	preorder(head);
	printf("\n");
	head=delete(head,10);
	printf("Preorder:\n");
	preorder(head);
	printf("\n");
}