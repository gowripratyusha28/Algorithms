#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Edge{
	int src,dst,weight;
};

struct Graph{
	int v,e;
	struct Edge *edge;
};

struct Graph *creategraph(int v1,int e1){
	struct Graph *graph;
	graph=(struct Graph *)malloc(v1*sizeof(struct Graph)); 
	graph->v=v1;
	graph->e=e1;
	graph->edge=(struct Edge *)malloc(e1*sizeof(struct Edge));
	return graph;
}

void addedge(struct Graph *graph,int i,int src,int dst,int weight){
	graph->edge[i].src=src;
	graph->edge[i].dst=dst;
	graph->edge[i].weight=weight;
}

void print(struct Graph *graph){
	printf("Vertices:%d\n",graph->v);
	printf("Edges:%d\n",graph->e);
	for(int i=0;i<graph->e;i++){
		printf("%d %d %d\n",graph->edge[i].src,graph->edge[i].dst,graph->edge[i].weight);
	}	
}

void merge(struct Graph *graph,int p,int q,int r){
	int n1=q-p+1;
	int n2=r-q;
	int i,j,k;
	struct Edge L[n1],R[n2];
	for(i=0;i<n1;i++){
		L[i].src=graph->edge[p+i].src;
		L[i].dst=graph->edge[p+i].dst;
		L[i].weight=graph->edge[p+i].weight;
	}
	for(j=0;j<n2;j++){
		R[j].src=graph->edge[q+j+1].src;
		R[j].dst=graph->edge[q+j+1].dst;
		R[j].weight=graph->edge[q+j+1].weight;
	}
	i=0,j=0,k=p;
	while(i<n1 && j<n2){
		if(L[i].weight <= R[j].weight){
			graph->edge[k].src=L[i].src;
			graph->edge[k].dst=L[i].dst;
			graph->edge[k].weight=L[i].weight;
			k++;
			i++;
		}
		else{
			graph->edge[k].src=R[j].src;
			graph->edge[k].dst=R[j].dst;
			graph->edge[k].weight=R[j].weight;
			k++;
			j++;
		}
	}
	while(i<n1){
		graph->edge[k].src=L[i].src;
		graph->edge[k].dst=L[i].dst;
		graph->edge[k].weight=L[i].weight;
		k++;
		i++;	
	}
	while(j<n2){
		graph->edge[k].src=R[j].src;
		graph->edge[k].dst=R[j].dst;
		graph->edge[k].weight=R[j].weight;
		k++;
		j++;
	}
}

void mergesort(struct Graph *graph,int p,int r){
	if(p<r){
		int q=(p+r)/2;
		mergesort(graph,p,q);
		mergesort(graph,q+1,r);
		merge(graph,p,q,r);
	}
}

struct subset{
	int parent;
	int rank;
};

int find(struct subset subsets[],int i){
	if(subsets[i].parent!=i){
		subsets[i].parent=find(subsets,subsets[i].parent);
	}
	return subsets[i].parent;
}

void Union(struct subset subsets[],int x,int y){
	int xroot=find(subsets,x);
	int yroot=find(subsets,y);
	if(subsets[xroot].rank < subsets[yroot].rank){
		subsets[xroot].parent=yroot;
	}
	else if(subsets[xroot].rank > subsets[yroot].rank){
		subsets[yroot].parent=xroot;
	}
	else{
		subsets[yroot].parent=xroot;
		subsets[xroot].rank++;
	}
}

void kruskalmst(struct Graph *graph){
	int V=graph->v;
	struct Edge result[V];
	int e,i;
	struct subset *subsets = (struct subset *)malloc(V*sizeof(struct subset));
	for(i=0;i<V;i++){
		subsets[i].parent=i;
		subsets[i].rank=0;
	}
	i=0;
	while(e<V-1 && i<graph->e){
		struct Edge nextedge=graph->edge[i++];
		int x=find(subsets,nextedge.src);
		int y=find(subsets,nextedge.dst);
		if(x!=y){
			result[e]=nextedge;
			//printf("  %d %d %d\n",result[e].src,result[e].dst,result[e].weight);
			e++;
			Union(subsets,x,y);
		}
	}
	for(i=0;i<e;i++){
		printf("%d  %d  %d\n",result[i].src,result[i].dst,result[i].weight);
	}
}

int main(){
	int v,e;
	printf("Enter v: ");
	scanf(" %d",&v);
	printf("Enter e: ");
	scanf(" %d",&e);
	int i,src,dst,weight;
	struct Graph *graph=creategraph(v,e);
	for(i=0;i<e;i++){
		printf("Enter src,dst,weight: ");
		scanf("%d %d %d",&src,&dst,&weight);
		addedge(graph,i,src,dst,weight);
	}
	print(graph);
	printf("\n");
	mergesort(graph,0,e-1);
	print(graph);
	printf("\n");
	kruskalmst(graph);
}