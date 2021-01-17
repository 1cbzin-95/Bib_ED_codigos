#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
# define Repeat 1000
struct lnode* new_lnode(int v);
struct hash* new_hash(int tamanho_tabela);
unsigned int fhash(struct hash* h, int v);
void hinsert (struct hash* h, int v);
float calculaMhash(int n,int m);
void limparMemoria(struct hash* h);
int busca_na_tabela(struct hash* h,int nBuscado);
void imprimir(struct hash* h);
struct lnode{
	int v;
	struct lnode *p;
};

struct hash{
	struct lnode **t;
	unsigned int m;
	unsigned int n;
};
int main(int argc,char *argv[]){
	struct timeval a,b;int t;
	srand(time(NULL));
	for(int totalnMax=10;totalnMax<1000;totalnMax+=10){
		struct hash* h = new_hash(2);
		for(int j=0;j<totalnMax;j++){//boto o j percorrer de 0 a n preenchendo
			hinsert(h,1+rand()%10000);//prenncher aleatorio
		}
		t=0;//zero o tempo
		for(int z=0;z<Repeat;z++){
			gettimeofday(&b,NULL);
			busca_na_tabela(h,1+rand()%10000);
			gettimeofday(&a,NULL);
			t=t+((a.tv_sec *1000000 + a.tv_usec)- (b.tv_sec*1000000 + b.tv_usec));
		}	
		printf("%d %f\n",totalnMax,(float)t/Repeat);	
		//imprimir(h);//caso queira ver a tabela comente o print de cima
		limparMemoria(h);
	} 
	return 0;
}
struct hash* new_hash(int tamanho_tabela){
	struct hash* h = (struct hash*)malloc(sizeof(struct hash));
	h->m = tamanho_tabela;
	h->t = (struct lnode**)malloc(h->m* sizeof(struct lnode*));
	for (int i = 0; i < h->m; i++)
		h->t[i] = NULL;
	h->n = 0;
	return h;
}

unsigned int fhash(struct hash* h, int v){
	return (v % h->m);
}
float calculaMhash(int n,int m){//ERRO AQUI
	if(n==0 || m==0)
		return 0;
	return (float)n/m;
}
void hinsert(struct hash* h, int v){
	struct lnode* w = new_lnode(v);//aloca e faz uma caixinha
	unsigned int p = fhash(h, v);//ver a posicao que coloca
	w->p = h->t[p];
	h->t[p] = w;
	h->n = h->n + 1;//incrementa o numero de elementos na tab
}
struct lnode* new_lnode(int v){
	struct lnode* w = (struct lnode*)malloc(sizeof(struct lnode));
	w->v = v;
	w->p =  NULL;
	return w;
}
void limparMemoria(struct hash* h){
	if(h!=NULL){//verifico se a hash num ta vazia
		struct lnode *aux;struct lnode *prox;//crio auxiliar pra recebendo as caixinha
		for(int i=0;i<h->m;i++){
			aux=h->t[i];
			while(aux!=NULL){
				prox=aux->p;
				free(aux);
				aux=prox;
			}
		}
		free(h);
	}
}
int busca_na_tabela(struct hash* h,int nBuscado){
	if(h!=NULL){//verifico se a hash num ta vazia
		struct lnode *aux;//crio auxiliar pra recebendo as caixinha
		unsigned int p=fhash(h,nBuscado);
		for(aux=h->t[p];aux!=NULL;aux=aux->p)
			if(aux->v==nBuscado)
				return 1;//se achar
	}
	return 0;//varreu nao achou
}
void imprimir(struct hash* h){
	if(h!=NULL){//verifico se a hash num ta vazia
		struct lnode *aux;//crio auxiliar pra recebendo as caixinha
		for(int i=0;i<h->m;i++){
			for(aux=h->t[i];aux!=NULL;aux=aux->p)
				printf("%d-",aux->v);
			printf("\n");
		}
		printf("\n");
		printf("------------nova tabela de 2 linha apenas pq nao faz rehash %d elementos--------\n\n",h->n);
	}
}
