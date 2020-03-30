#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

void printmatrix(int **mat,int v){
	int i,j;
	for(i=0;i<v;i++){
		for(j=0;j<v;j++){
			printf("%d%c",mat[i][j],(j==v-1)?'\n':' ');
		}
	}
}

int minkey(int D[],bool mstset[],int v){
	int min=INT_MAX,min_index;
	for(int i=0;i<v;i++){
		if(mstset[i]==false && D[i]<min){
			min=D[i];
			min_index=i;
		}
	}
	//printf("%d\n",min_index);
	return min_index;
}

int printmst(int parent[],int **graph,int D[],int v){
	int i;
	printf("Edge\tWeight\n");
	for(i=1;i<v;i++){
		printf("Entered\n");
		printf("%d - %d\t%d\n",parent[i],i,D[i]);
	}
}

void dijk(int **graph,int v){
	int parent[v],D[v],i,u,j;
	bool mstset[v];
	for(i=0;i<v;i++){
		D[i]=INT_MAX;
		mstset[i]=false;
	}
	D[0]=0;
	parent[0]=-1;
	for(i=0;i<v-1;i++){
		u=minkey(D,mstset,v);
		mstset[u]=true;
		printf("u:%d\n",u);
		for(j=0;j<v;j++){
			if(!mstset[j] && graph[u][j] && D[u]!=INT_MAX && D[u]+graph[u][j]<D[j]){
				printf("Ennnn:\n");
				parent[j]=u;
				D[j]=D[u]+graph[u][j];
			}
		}
		printmst(parent,graph,D,v);
	}
	printmst(parent,graph,D,v);
}

int main(){
	int e,v;
	printf("Enter v: ");
	scanf(" %d",&v);
	printf("Enter e: ");
	scanf(" %d",&e);
	int i,src,dst,weight;
	int **graph;
	graph=(int **)calloc(v,sizeof(int *));
	for(i=0;i<v;i++){
		graph[i]=(int *)calloc(v,sizeof(int));
	}
	for(i=0;i<e;i++){
		printf("Enter src,dst,weight: ");
		scanf(" %d%d%d",&src,&dst,&weight);
		graph[src][dst]+=weight;
	}
	printmatrix(graph,v);
	dijk(graph,v);
}