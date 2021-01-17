#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
# define Repeat 1000
int min(int* v, int n);
int max(int* v, int n);
void distributionSort(int* v,int n);
int main(int argc,char *argv[]){
	struct timeval a,b;int t;
	srand(time(NULL));
	int *pont;
	for(int n=1000;n<10000;n+=1000){//crio vetor de 1000 em 1000 posicao
		pont=(int *)malloc(n*sizeof(int));
		for(int j=0;j<n;j++){//boto o j percorrer de 0 a n
			pont[j]=1+random()%n;
		}
		t=0;//zero o tempo
		for(int z=0;z<Repeat;z++){//boto o z pecorrer Repeat vezes e retirando a mdeia
			gettimeofday(&b,NULL);
			distributionSort(pont,n);
			gettimeofday(&a,NULL);
			t=t+((a.tv_sec *1000000 + a.tv_usec)- (b.tv_sec*1000000 + b.tv_usec));
		}	
		printf("%d %f\n",n,(float)t/Repeat);	
	}
	free(pont);
	return 0;
}
void distributionSort(int* v,int n){
  int s = min(v,n);
  int g = max(v,n);
  int* c = (int*) malloc ((g-s+1)*sizeof(int));
  for (int i = 0; i < (g-s+1); i++)
		c[i] = 0;
  for (int i = 0; i < n; i++)
		c[v[i]-s]++;
  for (int i = 1; i < (g-s+1); i++){
		c[i] = c[i] + c[i-1];
  }

  int* w = (int*) malloc (n*sizeof(int));
  for (int i = 0; i< n; i++){
		int j = v[i] - s;
		w[c[j]-1] = v[i];
		c[j] = c[j] -1;
  }
  
  for (int i = 0; i<n ; i++){
    v[i] = w[i];
  }
  free(c);
  free(w);
}

int min(int* v, int n){
  int min = v[0];
  for (int i = 1; i<n; i++){
    if (v[i] < min){
      min = v[i];
    }
  }
  return min;
}

int max(int* v, int n){
  int max = v[0];
  for (int i = 1; i<n; i++){
    if (v[i] > max){
      max = v[i];
    }
  }
  return max;
}

