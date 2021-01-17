#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
# define Repeat 1000
int buscabinInter(int *v,int s,int n,int k);
int main(int argc,char *argv[]){
	struct timeval a,b;int t;
	srand(time(NULL));
	int *pont;
	for(int n=1000;n<10000;n+=1000){//crio vetor de 1000 em 1000 posicao
		pont=(int *)malloc(n*sizeof(int));
		for(int j=0;j<n;j++){//boto o j percorrer de 0 a n
			pont[j]=j+=1;
			//printf("%d \n",pont[j]); Pq vai precisa testar
		}
		t=0;//zero o tempo
		for(int z=0;z<Repeat;z++){//boto o z pecorrer Repeat vezes e retirando a mdeia
			gettimeofday(&b,NULL);
			buscabinInter(pont,0,n,n/2);
			gettimeofday(&a,NULL);
			t=t+((a.tv_sec *1000000 + a.tv_usec)- (b.tv_sec*1000000 + b.tv_usec));
		}	
		printf("%d %f\n",n,(float)t/Repeat);	
	}
	free(pont);
	return 0;
}
int buscabinInter(int *v,int s,int n,int k){
     int meio;//[0] [1] [2] [3] [4] [5] [6] [7] [8] [9] [10] =11posi
     while (s <= n){
          meio = (s + n)/2;
          if (k == v[meio])
               return meio;
          if (k < v[meio])
               n = meio-1;
          else
               s = meio+1;
     }
     return -1;   // não encontrei
}
