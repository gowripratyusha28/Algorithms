#include <stdio.h>
#include <stdlib.h>

int min(int a,int b){
	return (a<b)?a:b;
}

int BinDp(int n,int k){
	int B[n+1][k+1],i,j;
	for(i=0;i<=n;i++){
		for(j=0;j<=min(i,k);j++){
			if(j==0 || j==i){
				B[i][j]=1;
			}
			else{
				B[i][j]=B[i-1][j]+B[i-1][j-1];
			}
		}
	}
	return B[n][k];
}

int main(){
	int n,k;
	printf("Enter the numbers: ");
	scanf(" %d%d",&n,&k);
	if(n<k) printf("Not possible\n");
	else{
		printf("%d",BinDp(n,k));
	}
}