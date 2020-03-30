#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct adjlistnode{
  int dest;
  struct adjlistnode *next;
};
struct adjlist{
  struct adjlistnode *head;
};
struct graph{
  int v;
  struct adjlist *array;
};
struct graph *creategraph(int v){
  struct graph *Graph;
  Graph=(struct graph *)malloc(v*sizeof(struct graph)); 
  Graph->v=v;
  Graph->array=(struct adjlist *)malloc(v*sizeof(struct adjlist));
  int i;
  for(i=0;i<v;i++){
   Graph->array[i].head=NULL;
  }
 return Graph;
}
struct adjlistnode *newcr(int dest){
  struct adjlistnode *newnode;
  newnode=(struct adjlistnode *)malloc(sizeof(struct adjlistnode));
  newnode->dest=dest;
  newnode->next=NULL;
 return newnode;
}
void addedge(struct graph *Graph,int src,int dst){
  struct adjlistnode *new=newcr(dst);
  new->next=Graph->array[src].head;
  Graph->array[src].head=new;
  new=newcr(src);
  new->next=Graph->array[dst].head;
  Graph->array[dst].head=new;
}
void printgraph(struct graph *Graph){
  int v;
  for(v=0;v<Graph->v;v++){
   struct adjlistnode *pc=Graph->array[v].head;
   printf("Adjacency list of vertex %d:\n",v);
    while(pc!=NULL){
      printf("-> %d",pc->dest);
      pc=pc->next;
    }
   printf("\n"); 
  }
}
int main(){
  int v,a,b;
  char ch;
  printf("Enter no.of vertices: ");
  scanf(" %d",&v);
  struct graph *Graph;
  Graph=creategraph(v);
  printf("Enter: ");
  scanf(" %c",&ch);
  while(ch!='n'){
   printf("Enter 2 points: ");
   scanf(" %d%d",&a,&b);
   addedge(Graph,a,b);
   printf("Enter: ");
   scanf(" %c",&ch);
 
  }
  printgraph(Graph);
}
