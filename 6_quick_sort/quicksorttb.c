#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
# define Repeat 100
void quicksort(int *v,int s,int e);
int partition(int *v,int s,int e);
int main(int argc,char *argv[]){
	struct timeval a,b;int t;
	srand(time(NULL));
	int *pont;
	for(int n=100;n<5000;n+=100){//crio vetor de 1000 em 1000 posicao
		pont=(int *)malloc(n*sizeof(int));
		for(int j=0;j<n;j++){//boto o j percorrer de 0 a n
			pont[j]=1+random()%n+(random()%10);
		}
		t=0;//zero o tempo
		for(int z=0;z<Repeat;z++){//boto o z pecorrer Repeat vezes e retirando a mdeia
			gettimeofday(&b,NULL);
			quicksort(pont,0,n/2-1);
			gettimeofday(&a,NULL);
			t=t+((a.tv_sec *1000000 + a.tv_usec)- (b.tv_sec*1000000 + b.tv_usec));
		}	
		printf("%d %f\n",n,(float)t/Repeat);	
	}
	free(pont);
	return 0;
}
//recebe v,"s"-> inicio e "e"-> final
void quicksort(int *v,int s,int e){
	if(s<e){
		int p=partition(v,s,e);
		quicksort(v,s,p-1);
		quicksort(v,p+1,e);
	}
}
int partition(int *v,int s,int e){//s =inicio
	int i=s-1;
	for(int k=s;k<(e-1);k++){
		if(v[k]<v[e]){
			i+=1;
			v[i]=v[k];
		}
	}
	v[e]=v[i+1];
	return i+1;
}
