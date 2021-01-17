#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
# define Repeat 1000
typedef struct NO  *ArvBin;
struct NO{//um ponteiro de para ponteiros
	int info;
	struct NO *esq;
	struct NO *dir;
};
ArvBin *cria_arvore(void);
void libera_NO(struct NO *no);
int libera_arvBin(ArvBin *raiz);
int estaVazia(ArvBin *raiz);
int Altura_daArvore(ArvBin *raiz);
int inserir_ArvBin(ArvBin *raiz,int valor);
int busca_ArvBin(ArvBin *raiz,int valor);

int main(int argc,char *argv[]){
	struct timeval a,b;int t;
	srand(time(NULL));
	ArvBin *raiz=cria_arvore();// ponteiro para ponteiro para guardar a raiz e ir mudando a raiz ou cabeça da arvore
	for(int n=100;n<10000;n+=100){//crio vetor de 1000 em 1000 posicao
		for(int j=0;j<n;j++){//boto o j percorrer de 0 a n preenchendo
			inserir_ArvBin(raiz,j++);
		}
		t=0;//zero o tempo
		for(int z=0;z<Repeat;z++){//boto o z pecorrer Repeat vezes e retirando a mdeia
			gettimeofday(&b,NULL);
			busca_ArvBin(raiz,1+rand()%n);//nunca vai estar entao vai percorrer toda a arvore procurando
			gettimeofday(&a,NULL);
			t=t+((a.tv_sec *1000000 + a.tv_usec)- (b.tv_sec*1000000 + b.tv_usec));
		}	
		printf("%d %f\n",n,(float)t/Repeat);	
	}
	libera_arvBin(raiz);
	return 0;
}
//----------------------------------------------------------------------
ArvBin *cria_arvore(void){
	ArvBin *raiz=(ArvBin *)malloc(sizeof(ArvBin));//faz alocação
	if(raiz!=NULL)//verifica se alocou
		*raiz=NULL;//conteudo recebe NULL
	return raiz;//retorno a raiz
}
int libera_arvBin(ArvBin *raiz){
	if (raiz==NULL)
		return 2;
	libera_NO(*raiz);
	free(raiz);
	return 2;
}
void libera_NO(struct NO *no){
	if(no==NULL)
		return;
	libera_NO(no->esq);
	libera_NO(no->dir);
	no=NULL;	
}
int estaVazia(ArvBin *raiz){
	if(raiz==NULL)//se raiz nn tem 
		return 1;
	if(*raiz==NULL)//se conteudo e NUlo
		return 1;
	return 0;
}
int Altura_daArvore(ArvBin *raiz){
	if(estaVazia(raiz)!=1){//se nao der vazia faça
		int alt_esq=Altura_daArvore(&((*raiz)->esq));
		int alt_dir=Altura_daArvore(&((*raiz)->dir));
		if(alt_esq>alt_dir)
			return (alt_esq+1);
		else
			return (alt_dir+1);	
	}
	return 0;	
}
int inserir_ArvBin(ArvBin *raiz,int valor){
		if (raiz==NULL){
			return 0;
		}
		struct NO* novo=(struct NO*)malloc(sizeof(struct NO));//aloca o tamnho de um no
		if(novo==NULL){//verifica se deu certo a alocacao
			return 0;
		}
		novo->info=valor;
		novo->dir=NULL;
		novo->esq=NULL;
		//procura onde inserir------------------------------------------
		if(*raiz==NULL)//se for uma arvore vazia acrescenta
			*raiz=novo;
		else{//ja possui elementos na arvore
			struct NO* atual= *raiz;
			struct NO*ant=NULL;
			while(atual!=NULL){ //desce a arvore ate achar os NULL 
				ant=atual;
				if (valor==atual->info){
					free(novo);
					return 0;//ja existe na arvore
				}
				if(valor > atual->info){
					atual=atual->dir;
				}
				else{
					atual=atual->esq;
				}
			}
			if(valor>ant->info)
				ant->dir=novo;
			else
				ant->esq=novo;
		}
			return 1;
}
int busca_ArvBin(ArvBin *raiz,int valor){
	if (raiz==NULL)
		return 0;//vazia
	struct NO* atual=*raiz;//crio um no auxiliar pra ir percorrendo os nos da raiz
	while(atual != NULL){
		if(valor==atual->info)
			return 1;
	
		if(valor>atual->info)
			atual=atual->dir;
		else
			atual=atual->esq;
	}
	return -1;//percorreu e nao achou
}
