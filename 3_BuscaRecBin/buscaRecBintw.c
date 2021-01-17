#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
# define Repeat 1000
int buscaBinRec(int *v,int s,int n,int k);
int main(int argc,char *argv[]){
	struct timeval a,b;int t;
	srand(time(NULL));
	int *pont;
	for(int n=1000;n<10000;n+=1000){//crio vetor de 1000 em 1000 posicao
		pont=(int *)malloc(n*sizeof(int));
		for(int j=0;j<n;j++){//boto o j percorrer de 0 a n
			pont[j]=j+=1;
		}
		t=0;//zero o tempo
		for(int z=0;z<Repeat;z++){//boto o z pecorrer Repeat vezes e retirando a mdeia
			gettimeofday(&b,NULL);
			buscaBinRec(pont,0,n,20000);
			gettimeofday(&a,NULL);
			t=t+((a.tv_sec *1000000 + a.tv_usec)- (b.tv_sec*1000000 + b.tv_usec));
		}	
		printf("%d %f\n",n,(float)t/Repeat);	
		
	}
	free(pont);
	return 0;
}
int buscaBinRec(int *v,int s,int e,int k){
	int m=0;
	if(s<=e){//se inicio e menor ou igual ao fim
		m=(s+e)/2;
		if (v[m]==k){
			return m;
		}
		if(v[m]>k){
			return buscaBinRec(v,s,m-1,k);
		}
		return buscaBinRec(v,m+1,e,k);
	}
	return -1;
}
