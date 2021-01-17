#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
# define Repeat 1000
void merge(int *v,int s,int m,int e);
void  mergesort(int *v,int e,int n);
int main(int argc,char *argv[]){
	struct timeval a,b;int t;
	srand(time(NULL));
	int *pont;
	for(int n=1000;n<10000;n+=1000){//crio vetor de 1000 em 1000 posicao
		pont=(int *)malloc(n*sizeof(int));
		for(int j=0;j<n;j++){//boto o j percorrer de 0 a n
			pont[j]=1+random()%n;
			for(int z=0;z<j;z++){if(pont[z]==pont[j]){pont[j]=1+random()%n;}}
		}
		t=0;//zero o tempo
		for(int z=0;z<Repeat;z++){
			gettimeofday(&b,NULL);
			mergesort(pont,0,n);
			gettimeofday(&a,NULL);
			t=t+((a.tv_sec *1000000 + a.tv_usec)- (b.tv_sec*1000000 + b.tv_usec));
		}	
		printf("%d %f\n",n,(float)t/Repeat);	
	}
	free(pont);
	return 0;

}
//recebe v,"s"-> inicio e "e"-> final
void mergesort(int *v,int s,int e){
	if(s<e){
		int m=(s+e)/2;
		mergesort(v,s,m);
		mergesort(v,m+1,e);
		merge(v,s,m,e);
	}
}
void merge(int *v,int s,int m,int e){
	int i=s;
	int j=m+1;int tam=e-s+1;//para vetor auxiliar w
	int *w=(int *)malloc(tam*sizeof(int));
	for(int k=1;k<(e-s+1);k++){
		if((j>e)||((i<=m)&&(v[i]<v[j]))){
			w[k]=v[i];
			i+=1;
		}
		else{
			w[k]=v[j];
			j=j+1;
		}
	}
	for(int k=1;k<(e-s+1);k++){
		v[s+k-1]=w[k];		
	}
	free(w);
}
