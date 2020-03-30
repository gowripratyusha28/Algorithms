#include <stdio.h>
#include <stdlib.h>
int time=0;

struct node{
  int vertex;
  struct node *next;
};
struct Graph{
	int numVertices;
	struct node **adjlist;
        int *visited;
        int *start;
        int *finish;
        int *parent;
};
struct Graph *creategraph(int v){
  struct Graph *graph;
  graph=(struct Graph *)malloc(v*sizeof(struct Graph)); 
  graph->numVertices=v;
  graph->adjlist=(struct node **)malloc(v*sizeof(struct node *));
  graph->visited=(int *)malloc(v*sizeof(int));
  graph->start=(int *)malloc(v*sizeof(int));
  graph->finish=(int *)malloc(v*sizeof(int));
  graph->parent=(int *)malloc(v*sizeof(int));
  int i;
  for(i=0;i<v;i++){
   graph->adjlist[i]=NULL;
   graph->visited[i]=0;
   graph->start[i]=0;
   graph->finish[i]=0;
   graph->parent[i]=0;
  }
 return graph;
}
struct node *createnode(int dest){
  struct node *newnode;
  newnode=(struct node *)malloc(sizeof(struct node));
  newnode->vertex=dest;
  newnode->next=NULL;
 return newnode;
}
void addedge(struct Graph *graph,int src,int dst){
  struct node *new=createnode(dst);
  new->next = graph->adjlist[src-1];
  graph->adjlist[src-1] = new;
  new=createnode(src);
  new->next=graph->adjlist[dst-1];
  graph->adjlist[dst-1]=new;
}
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjlist[v];
        printf("\n Adjacency list of vertex %d\n ", v+1);
        while (temp)
        {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}
/*void dfs(struct Graph *graph,int vertex){
  struct node *adjlist = graph->adjlist[vertex-1];
  struct node *temp = adjlist;
        
        graph->visited[vertex-1] = 1;
        printf("Visited %d \n", vertex);
        while(temp!=NULL) {
            int connectedVertex = temp->vertex;
        
            if(graph->visited[connectedVertex-1] == 0) {
                dfs(graph, connectedVertex);
            }
            temp = temp->next;
        } 
}*/
void dfs(struct Graph *graph,int vertex){
  graph->visited[vertex-1]=1;
  time+=1;
  graph->start[vertex-1]=time;
  printf("Visited vertex %d\n",vertex);
  struct node* temp = graph->adjlist[vertex-1]; 
   while(temp) {
            int adjVertex = temp->vertex;
            if(graph->visited[adjVertex-1] == 0){
                graph->parent[adjVertex-1] = vertex;
                dfs(graph,adjVertex);
                                
          }
            temp = temp->next;
       }
   graph->finish[vertex-1]=time;
}
int main(){
  int v,e,a,b,i;
  printf("Enter v: ");
  scanf(" %d",&v);
  printf("Enter e: ");
  scanf(" %d",&e);
  struct Graph *graph=creategraph(v);
  for(i=0;i<e;i++){
   printf("Enter: ");
   scanf(" %d%d",&a,&b);
   addedge(graph,a,b);
  }
  printGraph(graph);
  printf("\n");
  dfs(graph,1);
  for(i=0;i<e;i++){
   printf("Start time %d is %d\n",i+1,graph->start[i]);
  }
  for(i=0;i<e;i++){
   printf("Finish time %d is %d\n",i+1,graph->finish[i]);
  }
}  











