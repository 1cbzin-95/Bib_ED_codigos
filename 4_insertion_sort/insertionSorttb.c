#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
# define Repeat 1000
int insertionsort(int *v,int e,int n);
int main(int argc,char *argv[]){
	struct timeval a,b;int t;
	srand(time(NULL));
	int *pont;
	for(int n=1000;n<100000;n+=1000){//crio vetor de 1000 em 1000 posicao
		pont=(int *)malloc(n*sizeof(int));
		for(int j=0;j<n;j++){//boto o j percorrer de 0 a n
			pont[j]=j+=1;
			//printf("%d \n",pont[j]); Pq vai precisa testar
		}
		t=0;//zero o tempo
		for(int z=0;z<Repeat;z++){
			gettimeofday(&b,NULL);
			insertionsort(pont,0,n);
			gettimeofday(&a,NULL);
			t=t+((a.tv_sec *1000000 + a.tv_usec)- (b.tv_sec*1000000 + b.tv_usec));
		}	
		printf("%d %f\n",n,(float)t/Repeat);	
	}
	free(pont);
	return 0;
}
int insertionsort(int *v,int e,int n){
	if(e < n){
		int i=e+1;
		while((i>1)&&(v[i]<v[i-1])){
			v[i]=v[i-1];
			i-=1;
		}
		insertionsort(v,e+1,n);		
	}
	return 0;
}	
