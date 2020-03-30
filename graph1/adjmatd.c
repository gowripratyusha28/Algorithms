#include <stdio.h>
#include <stdlib.h>
void readgraph(int **a,int *indegree,int *outdegree,int n){
 int i,j;
 int v1,v2;
 char ch;
 printf("Enter y or n: ");
 scanf(" %c",&ch);
 while(ch!='n'){
  printf("Enter the vertices: "); 
  scanf(" %d%d",&v1,&v2);
  indegree[v2]+=1;
  outdegree[v1]+=1;
  a[v1][v2]+=1;
  printf("Enter y or n: ");
  scanf(" %c",&ch);
 }
}
void printgraph(int **a,int *indegree,int *outdegree,int n){
 int i,j,k,m;
 for(i=0;i<n;i++){
 if(i==0){
  printf("  ");
  printf("%d ",i);
  }
 else if(i==n-1){
  printf("%d ",i);
  printf("i ");
  printf("o");
 }
 else{
  printf("%d ",i);
  }
 }
 printf("\n");
 for(m=0,j=0;j<n;j++){
  for(k=0;k<n;k++){
   if(k==0){
    printf("%d ",m);
    printf("%d ",a[j][k]);
   }
   else if(k==n-1){
    printf("%d ",a[j][k]);
    printf("%d ",indegree[i]);
    printf("%d\n",outdegree[i]);
   }
   else{
    printf("%d ",a[j][k]);
   }
  }
  m++;
 }
}
int main(){
 int **g,*indegree,*outdegree;
 int n,i;
 printf("Enter no.of vertices: ");
 scanf(" %d",&n);
 g=(int **)calloc(n,sizeof(int *));
 for(i=0;i<n;i++){
  g[i]=(int *)calloc(n,sizeof(int));
 }
 indegree=(int *)calloc(n,sizeof(int));
 outdegree=(int *)calloc(n,sizeof(int));
 readgraph(g,indegree,outdegree,n);
 printgraph(g,indegree,outdegree,n);
}
