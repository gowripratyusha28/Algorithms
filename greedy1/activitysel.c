#include <stdio.h>
#include <stdlib.h>

struct Activity{
	int start;
	int finish;
};

struct Prob{
	int n;
	struct Activity *activity;
};

struct Prob *createprob(int n1){
	struct Prob *prob;
	prob = (struct Prob *)malloc(n1*sizeof(struct Prob));
	int i;
	prob->n=n1;
	prob->activity=(struct Activity *)malloc(n1*sizeof(struct Activity));
	return prob;
}

void add(struct Prob *prob,int st,int ft,int i){
	prob->activity[i].start=st;
	prob->activity[i].finish=ft;
}

void merge(struct Prob *prob,int p,int q,int r){
	int n1=q-p+1;
	int n2=r-q;
	int i,j,k;
	struct Activity *L,*R;
	L = (struct Activity *)malloc(n1*sizeof(struct Activity));
	R = (struct Activity *)malloc(n2*sizeof(struct Activity));
	for(i=0;i<n1;i++){
		L[i].start=prob->activity[p+i].start;
		L[i].finish=prob->activity[p+i].finish;
	}
	for(j=0;j<n2;j++){
		R[j].start=prob->activity[q+j+1].start;
		R[j].finish=prob->activity[q+j+1].finish;
	}
	i=0,j=0,k=p;
	while(i<n1 && j<n2){
		if(L[i].finish <= R[j].finish){
			prob->activity[k].finish=L[i].finish;
			prob->activity[k].start=L[i].start;
			k++;
			i++;
		}
		else{
			prob->activity[k].start=R[j].start;
			prob->activity[k].finish=R[j].finish;
			k++;
			j++;
		}
	}
	while(i<n1){
		prob->activity[k].start=L[i].start;
		prob->activity[k].finish=L[i].finish;
		i++;
		k++;
	}
	while(j<n2){
		prob->activity[k].start=R[j].start;
		prob->activity[k].finish=R[j].finish;
		k++;
		j++;
	}
}

void mergesort(struct Prob *prob,int p,int r){
	if(p<r){
		int q=(p+r)/2;
		mergesort(prob,p,q);
		mergesort(prob,q+1,r);
		merge(prob,p,q,r);
	}
}

void print(struct Prob *prob,int n){
	int i;
	printf("n:%d\n",prob->n);
	printf("st: ");
	for(i=0;i<n;i++){
		printf("%2d  ",prob->activity[i].start);
	}
	printf("\n");
	printf("ft: ");
	for(i=0;i<n;i++){
		printf("%2d  ",prob->activity[i].finish);
	}
}

void actsel(struct Prob *prob){
	int i=0,j;
	printf("(");
	printf("%d,%d",prob->activity[i].start,prob->activity[i].finish);
	printf(")");
	for(j=1;j<prob->n;j++){
		if(prob->activity[j].start >= prob->activity[i].finish){
			printf("(%d,%d)",prob->activity[j].start,prob->activity[j].finish);
			i=j;
		}
	}
}

int main(){
	int n,i,start,finish;
	printf("Enter no.of activities: ");
	scanf(" %d",&n);
	struct Prob *prob;
	prob = createprob(n);
	for(i=0;i<n;i++){
		printf("Enter st and ft of %2d : ",i+1);
		scanf(" %d%d",&start,&finish);
		add(prob,start,finish,i);
	}
	print(prob,n);
	printf("\n");
	mergesort(prob,0,n-1);
	print(prob,n);
	printf("\n");
	actsel(prob);
	printf("\n");
}