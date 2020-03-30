#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

struct node{
  int vertex;
  int weight;
  struct node *next;
};

struct Graph{
	int numVertices;
	struct node **adjlist;
  //int *visited;
};

struct Graph *creategraph(int v){
  struct Graph *graph;
  graph=(struct Graph *)malloc(v*sizeof(struct Graph)); 
  graph->numVertices=v;
  graph->adjlist=(struct node **)malloc(v*sizeof(struct node *));
  //graph->visited=(int *)malloc(v*sizeof(int));
  //graph->d=(int *)malloc(v*sizeof(int));
  int i;
  for(i=0;i<v;i++){
   graph->adjlist[i]=NULL;
   //graph->visited[i]=0;
  }
 return graph;
}

struct node *createnode(int dest,int weight){
  struct node *newnode;
  newnode=(struct node *)malloc(sizeof(struct node));
  newnode->vertex=dest;
  newnode->weight=weight;
  newnode->next=NULL;
 return newnode;
}

void addedge(struct Graph *graph,int src,int dst,int weight){
  struct node *new=createnode(dst,weight);
  new->next = graph->adjlist[src];
  graph->adjlist[src] = new;
  new=createnode(src,weight);
  new->next=graph->adjlist[dst];
  graph->adjlist[dst]=new;
  printf("added\n");
}

void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjlist[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf(" -> %d(%d)", temp->vertex,temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

int minkey(int key[],bool mstset[],int v){
	int min=INT_MAX,min_index;
	for(int i=0;i<v;i++){
		if(mstset[i]==false && key[i]<min){
			min=key[i];
			min_index=i;
		}
	}
	//printf("%d\n",min_index);
	return min_index;
}

int printmst(int parent[],struct Graph *graph,int key[]){
	int v=graph->numVertices;
	printf("Edge\tWeight\n");
	for(int i=1;i<v;i++){
		//printf("Entered\n");
		printf("%d - %d\t%d\n",parent[i],i,key[i]);
	}
}

void primmst(struct Graph *graph,int v){
	int parent[v],key[v],i,u;
	bool mstset[v];
	for(i=0;i<v;i++){
		key[i]=INT_MAX;
		mstset[i]=false;
	}
	key[0]=0;
	parent[0]=-1;
	for(i=0;i<v-1;i++){
		u=minkey(key,mstset,v);
		mstset[u]=true;
		printf("u:%d\n",u);
		struct node *temp=graph->adjlist[u];
		while(temp){
			if(temp && mstset[temp->vertex]==false && temp->weight<key[temp->vertex]){
				parent[temp->vertex]=u;
				key[temp->vertex]=temp->weight;	
			}
			temp=temp->next;
		}
		printmst(parent,graph,key);
	}
	printmst(parent,graph,key);
}

int main(){
	int v,e,i,j,src,dst,weight;
    printf("Enter v: ");
    scanf(" %d",&v);
  	struct Graph *graph=creategraph(v);
  	printf("Enter e: ");
  	scanf(" %d",&e);
  	for(i=0;i<e;i++){
    	printf("Enter src,dst,weight: ");
    	scanf(" %d%d%d",&src,&dst,&weight);
    	addedge(graph,src,dst,weight);
  	}
  	printGraph(graph);
  	printf("\n");
  	primmst(graph,v);
}