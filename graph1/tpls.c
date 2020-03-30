#include <stdio.h>
#include <stdlib.h>
int time=0;

struct node{
  int vertex;
  struct node *next;
};

// typedef is used for user defined type node

typedef struct stack node;


// Another user defined type nodeptr is pointer to node type 

typedef node * nodeptr;

struct Graph{
	int numVertices;
	struct node **adjlist;
        int *visited;
        int *start;
        int *finish;
        int *parent;
};

int topstack(nodeptr f);

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
  /*new=createnode(src);
  new->next=graph->adjlist[dst-1];
  graph->adjlist[dst-1]=new;*/
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
struct stack{
                int data;
                struct stack *next;
};


void init(nodeptr *top)
{
  *(top)=NULL; // empty stack
}

//================================================================
void push(nodeptr *top,int d)
{
    node * newnode; // use a pointer type for node called newnode
    newnode=(node*)malloc(sizeof(node)); // allocate space for node type pointed to by newnode
    newnode->next=*(top); *(top)=newnode; 
// newnode points to node type that stored the old top stack pointer
// finally we return newnode by reference through top of type nodeptr*
    //printf("\nEnter the character to push\n");
    //fflush(stdin);
    //scanf(" %c",&(newnode->data)); // read data in node type space for data of type char 
//                            where the node is pointed to by the new node pointed to by nodeptr
     newnode->data=d;
	 //topstack(*(top)); // Now simply print what was pushed on top of stack
}

//===============================================================
void pop(nodeptr *top)
{
       node *delnode;      /* pointer to node to be deleted */


	 topstack(*(top)); // first simply print what is going to be pooped off the stack top
  
      if (*(top)==NULL) printf("cannot pop"); 	
    // No deletion is possible if the list is already empty
       else  {delnode=*(top); // if non-empty then pick the top node pointer through top which is of 
//                                                              type nodeptr*
        *top=(*top)->next; free(delnode); } // move down one step in stack, changing contents of 
                                            // location pointed to by top and free the node popped off
	
    }

//================================================================
int topstack(nodeptr f)
{
	// Simply print the data pointed to by node pointer
        if (f==NULL) return 0; 
        else{
			//printf("top value=%d",f->data);
			 return f->data;
		}
}

int isempty(nodeptr f){
  if(f==NULL) return 1;
  else return 0;
}

void dfs(struct Graph *graph,int vertex,nodeptr *top){
  graph->visited[vertex-1]=1;
  time+=1;
  graph->start[vertex-1]=time;
  printf("Visited vertex %d\n",vertex);
  struct node *temp=graph->adjlist[vertex-1];
  while(temp){
    int adjVertex=temp->vertex;
    if(graph->visited[adjVertex-1]==0){
      graph->parent[adjVertex-1]=vertex;
      dfs(graph,adjVertex,top);
    }
    temp=temp->next;
  }
  graph->finish[vertex-1]=time;
  push(top,vertex);
}

void tpls(struct Graph *graph){
  nodeptr top;
  init(&top);
  int i;
  for(i=0;i<graph->numVertices;i++){
    if(graph->visited[i]==0){
      dfs(graph,i+1,&top);
    }
  }
  while(!isempty(top)){
    //printf("hi");
    printf("%d  ",topstack(top));
    pop(&top);
  }
}

int main(){
  int v,e,a,b,i;
  nodeptr link;
  init(&link);
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
  tpls(graph);
  for(i=0;i<v;i++){
   printf("\nStart time of vertex %d is %d",i+1,graph->start[i]);
  }
  for(i=0;i<v;i++){
   printf("\nFinish time of vertex %d is %d",i+1,graph->finish[i]);
  }
  printf("\n");
}  

