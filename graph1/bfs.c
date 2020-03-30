#include <stdio.h>
#include <stdlib.h>

struct node{
  int vertex;
  struct node *next;
};
struct Graph{
	int numVertices;
	struct node **adjlist;
        int *visited;
};
struct Graph *creategraph(int v){
  struct Graph *graph;
  graph=(struct Graph *)malloc(v*sizeof(struct Graph)); 
  graph->numVertices=v;
  graph->adjlist=(struct node **)malloc(v*sizeof(struct node *));
  graph->visited=(int *)malloc(v*sizeof(int));
  //graph->d=(int *)malloc(v*sizeof(int));
  int i;
  for(i=0;i<v;i++){
   graph->adjlist[i]=NULL;
   graph->visited[i]=0;
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

struct queue{
                int data;
                struct queue *next;
};

typedef struct queue node;

typedef node * nodeptr;

void init(nodeptr *front,nodeptr *rear)
{
  *(rear)=*(front)=NULL;
}

void enqueue(nodeptr *front,nodeptr *rear,int d)
{
    node * newnode;
    //node * temp;      /* New node to be inserted */
    newnode=(node*)malloc(sizeof(node));
    newnode->next=NULL;
    newnode->data=d;
    //printf("\nEnter the character to push\n");
    //fflush(stdin);
    //scanf(" %c",&(newnode->data));
    // Two cases arise, inserting into (i) empty queue (ii) non-empty queue
    if(*(front)==NULL && *(rear)==NULL)
    {
	    // For empty queue front and rear are same after inertion
        *(front)=newnode;
        *(rear)=newnode;
    }
    else
    {  // For non-empty queue, rear is first saved in temp, newnode is added at the end (rear), and
	   // finally rear is made to point to the end of the list, that is, newnode 
	    //temp=*(rear);
            //temp->next=newnode;
           //*(rear)=newnode;
	   (*(rear))->next=newnode;
	   (*(rear))=(*(rear))->next;
	   //display(*(rear));
    }
}
//===============================================================
int dequeue(nodeptr *front,nodeptr *rear)
{
    node *delnode;      /* Node to be deleted */
    // No deletion is possible if the list is already empty
    if(*(front)==NULL && *(rear)==NULL)
        printf("\nQueue is empty to delete any element\n");
    else
    { // If non-empty, two cases arise (i) list has one node (ii) list has more than one node
	    if (*(front)==*(rear)) {
		    // If list has one node then both front and rear become NULL after deletion
        delnode=*(front);
        //free(delnode); 
	*(front)=NULL; *(rear)=NULL;
        return delnode->data;   
     } // Deleted node is also freed
	else {// If there are two or mode nodes then simply front is moved forward to next node and
		// first node is freed
	delnode=*(front);
        //*(front)=delnode->next;
	(*(front))=(*(front))->next;
        //free(delnode);
        return delnode->data;
         }
      }
    }
//================================================================
void display(nodeptr f)
{
	// Simply print the data in all nodes of the list, if any; otherwise, do nothing.
	if (f==NULL) printf("List is empty \n");
    printf("Queue is: ");
    while(f!=NULL)
    {
        printf(" %d ",f->data);
        f=f->next;
    }
}
int isempty(nodeptr f){
  if(f==NULL) return 1;
  else return 0;
}
void bfs(struct Graph *graph,int startVertex,int *d,int *parent){
  nodeptr front,rear;
  init(&front,&rear);
  graph->visited[startVertex-1]=1;
  d[startVertex-1]=0;
  parent[startVertex]=startVertex;
  enqueue(&front,&rear,startVertex);
  while(!(isempty(front))){
   display(front);
   printf("\n");
   int curVertex=dequeue(&front,&rear);
   printf("Visited vertex %d\n",curVertex);
   struct node* temp = graph->adjlist[curVertex-1]; 
       while(temp) {
            int adjVertex = temp->vertex;
            if(graph->visited[adjVertex-1] == 0){
                graph->visited[adjVertex-1] = 1;
                d[adjVertex-1]=d[curVertex-1]+1;
                parent[adjVertex-1]=curVertex;
                enqueue(&front,&rear,adjVertex);
            }
            temp = temp->next;
       }
    }
}
int main(){
  int v,e,i,a,b,*d,*parent;
  printf("Enter v: ");
  scanf(" %d",&v);
  printf("Enter e: ");
  scanf(" %d",&e);
  d=(int *)calloc(v,sizeof(int));
  parent=(int *)calloc(v,sizeof(int));
  struct Graph *graph=creategraph(v);
  for(i=0;i<e;i++){
   printf("Enter: ");
   scanf(" %d%d",&a,&b);
   addedge(graph,a,b);
  }
  printGraph(graph);
  printf("\n");
  bfs(graph,1,d,parent);
  printf("\n");
  for(i=0;i<v;i++){
    printf("Distance of vertex %d from start is %d\n",i+1,d[i]);
  }
  for(i=0;i<v;i++){
    printf("parent of vertex %d is %d\n",i+1,parent[i]);
  }
}





