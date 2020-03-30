#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void matrix_chain_order(int **m,int **s,int *P,int n){
	int i,j,l,k,x;
	for(i=1;i<=n;i++){
		m[i][i]=0;
	}
	for(l=1;l<=n-1;l++){
		for(i=1;i<=n-l;i++){
			j=i+l;
			m[i][j]=INT_MAX;
			for(k=i;k<=j-1;k++){
				x=m[i][k]+m[k+1][j]+P[i-1]*P[k]*P[j];
				if(x<m[i][j]){
					m[i][j]=x;
					s[i][j]=k;
				}
			}
		}
	}
}

void print_matrix(int **a,int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%2d%c",a[i][j],(j==n-1)?'\n':' ');
		}
	}
}

void print(int **s,int i,int j){
	if(i==j){
		printf("%c%d",'A',i);
	}
	else{
		printf("(");
		print(s,i,s[i][j]);
		print(s,s[i][j]+1,j);
		printf(")");
	}
}

int main(){
	int n;
	printf("Enter no.of matrices: ");
	scanf(" %d",&n);
	int *P,i;
	for(i=0;i<n+1;i++){
		printf("Enter: ");
		scanf(" %d",&P[i]);
	}
	int **m,**s;
	m=(int **)calloc(n+1,sizeof(int *));
	for(i=0;i<=n;i++){
		m[i]=(int *)calloc(n+1,sizeof(int));
	}
	s=(int **)calloc(n+1,sizeof(int *));
	for(i=0;i<=n;i++){
		s[i]=(int *)calloc(n+1,sizeof(int));
	}
	matrix_chain_order(m,s,P,n);
	printf("m:\n");
	print_matrix(m,n+1);
	printf("s:\n");
	print_matrix(s,n+1);
	print(s,1,n);
}