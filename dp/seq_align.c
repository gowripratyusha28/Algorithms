#include <stdio.h>
#include <stdlib.h>

void seq(int **l,int m,int n,int *x,int *y,int gp,int mis){
	int i,j;
	for(j=0;j<n;j++){
		l[m][j]=gp*(n-j);
	}
	for(i=0;i<m;i++){
		l[i][n]=gp*(m-i);
	}
	for(sum=m+n;sum>=m;sum--){
		for(i=m;i>=sum-n;i--){
			j=sum-i;
			if(i==m ||j==n){
				
			}
		}
	}	
}