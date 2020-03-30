#include <stdio.h>
#include <stdlib.h>

void heapifymax(int *A,int n,int i){
	if(2*i>n) return;
	int midx;
	midx=(2*i==n)?2*i:(A[2*i]>A[2*i+1])?2*i:2*i+1;
	if(A[midx]>A[i]){
		int temp;
		temp=A[midx];
		A[midx]=A[i];
		A[i]=temp;
		heapifymax(A,n,midx);
	}
}

void buildheap(int *A,int n){
	int i=n/2;
	while(i){
		heapifymax(A,n,i);
		i--;
	}
}

void heapsort(int *A,int n){
	buildheap(A,n);
	int i;
	for(i=n;i>=2;i--){
		int temp;
		temp=A[i];
		A[i]=A[1];
		A[1]=temp;
		n=n-1;
		heapifymax(A,n,1);
	}
}

int maxheap(int *A){
	return A[1];
}

void delete(int *A,int n){
	int lastelem=A[n];
	A[1]=lastelem;
	n=n-1;
	heapifymax(A,n,1);
}


void siftup(int *A,int n,int i){
	int parent=i/2;
	if(parent>1){
		if(A[i]<A[parent]){
			int temp;
			temp=A[i];
			A[i]=A[parent];
			A[parent]=temp;
			siftup(A,n,parent);
		}
	}
}

void insert(int *A,int n,int key){
	//n=n+1;
	A[n]=key;
	siftup(A,n,n);
}

int main(){
	int *A,n,key;
	printf("Enter n: ");
	scanf(" %d",&n);
	A=(int *)malloc(n+1*sizeof(int));
	int i;
	for(i=1;i<=n;i++){
		scanf(" %d",&A[i]);
	}
	buildheap(A,n);
	//heapsort(A,n);
	for(i=1;A[i]!='\0';i++){
		printf("%d  ",A[i]);
	}
	printf("Enter elem to insert: ");
	scanf(" %d",&key);
	n+=1;
	A=(int *)realloc(A,n+1*sizeof(int));
	insert(A,n,key);
	for(i=1;A[i]!='\0';i++){
		printf("%d  ",A[i]);
	}
	printf("\n");
}