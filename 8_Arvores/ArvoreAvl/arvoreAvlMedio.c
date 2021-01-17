#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
# define Repeat 1000
typedef struct NO  *ArvAvl;
struct NO{//um ponteiro de para ponteiros
	int info;
	int alt;//altura da subarvore
	struct NO *esq;
	struct NO *dir;
};
ArvAvl *cria_arvore(void);
void libera_NO(struct NO *no);
int libera_ArvAvl(ArvAvl *raiz);
int estaVazia(ArvAvl *raiz);
int busca_ArvAvl(ArvAvl *raiz,int valor);
int alt_NO(struct NO* no);
int fatorBalanceamento_no(struct NO* no);
int maior(int x,int y);
void rotacaoLL(ArvAvl *raiz);
void rotacaoRR(ArvAvl *raiz);
void rotacaoLR(ArvAvl *raiz);//dupla rotacao
void rotacaoRL(ArvAvl *raiz);//dupla rotacao
int inserir_ArvAvl(ArvAvl *raiz,int valor);
struct NO* procuraMenor(struct NO* atual);
int remove_EmementAvl(ArvAvl *raiz,int valor);

int main(int argc,char *argv[]){
	struct timeval a,b;int t;
	srand(time(NULL));
	ArvAvl *raiz=cria_arvore();// ponteiro para ponteiro para guardar a raiz e ir mudando a raiz ou cabeça da arvore
	for(int n=10;n<10000;n+=10){//crio vetor de 1000 em 1000 posicao
		for(int j=0;j<n;j++){//boto o j percorrer de 0 a n preenchendo
			inserir_ArvAvl(raiz,j);
		}
		t=0;//zero o tempo
		for(int z=0;z<Repeat;z++){//boto o z pecorrer Repeat vezes e retirando a mdeia
			gettimeofday(&b,NULL);
			busca_ArvAvl(raiz,n/2);//nunca vai estar entao vai percorrer toda a arvore procurando
			gettimeofday(&a,NULL);
			t=t+((a.tv_sec *1000000 + a.tv_usec)- (b.tv_sec*1000000 + b.tv_usec));
		}	
		printf("%d %f\n",n,(float)t/Repeat);	
	}
	libera_ArvAvl(raiz);
	return 0;
}
ArvAvl *cria_arvore(void){
	ArvAvl *raiz=(ArvAvl *)malloc(sizeof(ArvAvl));//faz alocação
	if(raiz!=NULL)//verifica se alocou
		*raiz=NULL;//conteudo recebe NULL
	return raiz;//retorno a raiz
}
int libera_ArvAvl(ArvAvl *raiz){
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
int estaVazia(ArvAvl *raiz){
	if(raiz==NULL)//se raiz nn tem 
		return 1;
	if(*raiz==NULL)//se conteudo e NUlo
		return 1;
	return 0;
}
int inserir_ArvAvl(ArvAvl *raiz,int valor){
	int resp;
	if(*raiz==NULL){
		struct NO* novo=(struct NO*)malloc(sizeof(struct NO));//aloca o tamnho de um no
		if(novo==NULL)//verifica se deu certo a alocacao
			return 0;
		novo->info=valor;
		novo->alt=0;
		novo->dir=NULL;
		novo->esq=NULL;//se for uma arvore vazia acrescenta
		*raiz=novo;
		return 1;
	}
	struct NO* atual= *raiz;//ja possui elementos na arvore
	if (valor<atual->info){
		if((resp=inserir_ArvAvl(&(atual->esq),valor))==1){//se a insercao funcional preciso balancear
			if(fatorBalanceamento_no(atual)>=2){
				if(valor <(*raiz)->esq->info)
					rotacaoLL(raiz);
				else
					rotacaoLR(raiz);
			}
		}
	}
	else{//no caso de nao ser menor
		if (valor > atual->info){
			if((resp=inserir_ArvAvl(&(atual->dir),valor))==1){//se a insercao funcional preciso balancear
				if(fatorBalanceamento_no(atual)>=2){
					if((*raiz)->dir->info < valor)
						rotacaoRR(raiz);
					else
						rotacaoRL(raiz);
				}
			}
		}
		else{
			return 0;//o valor ja existe
		}	
	}
	atual->alt=maior(alt_NO(atual->esq),alt_NO(atual->dir))+1;
	return resp;
}
int busca_ArvAvl(ArvAvl *raiz,int valor){
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
int alt_NO(struct NO* no){//------------Pega Altura de um no----
	if (no==NULL)//no nao existe
		return -1;
	return no->alt;//retorno a altura dele
}
//------------Calcula fator de balanceamento de um nó---
int fatorBalanceamento_no(struct NO* no){//fator positivo inserir no lado esquerdo;negativo lado direito
	return labs(alt_NO(no->esq)-alt_NO(no->dir));//saber a diferença em modulo.labs
}
int maior(int x,int y){//------------calcula maior entre 2 valores------------
	if(x>y)
		return x;
	return y;
}
void rotacaoLL(ArvAvl *raiz){//inseriu do lado esquerdo Fazer rotacao para direita
	struct NO* no;
	no=(*raiz)->esq;
	(*raiz)->esq=no->dir;
	no->dir=*raiz;
	(*raiz)->alt=maior(alt_NO((*raiz)->esq),alt_NO((*raiz)->dir)+1);
	no->alt=maior(alt_NO(no->esq),((*raiz)->alt)+1);
	*raiz=no;	
}
void rotacaoRR(ArvAvl *raiz){//inseriu do lado direito Fazer rotacao para esquerda
	struct NO* no;
	no=(*raiz)->dir;
	(*raiz)->dir=no->esq;
	no->esq=*raiz;
	(*raiz)->alt=maior(alt_NO((*raiz)->esq),alt_NO((*raiz)->dir)+1);
	no->alt=maior(alt_NO(no->dir),((*raiz)->alt)+1);
	*raiz=no;	
}
void rotacaoLR(ArvAvl *raiz){
	rotacaoRR(&(*raiz)->esq);
	rotacaoLL(raiz);
}
void rotacaoRL(ArvAvl *raiz){
	rotacaoLL(&(*raiz)->dir);
	rotacaoRR(raiz);
}
struct NO* procuraMenor(struct NO* atual){//procurar o menor
	struct NO *no1=atual;
	struct NO *no2=atual->esq;
	while(no2 != NULL){
		no1=no2;
		no2=no2->esq;
	}
	return no1;
}
int remove_EmementAvl(ArvAvl *raiz,int valor){//BUscar e remover o no e deixar balanceado
	if(*raiz==NULL)
		return 0;
	int res;
	if(valor<(*raiz)->info){
		if((res=remove_EmementAvl(&(*raiz)->esq,valor))==1)
			if(fatorBalanceamento_no(*raiz)>=2){
				if(alt_NO((*raiz)->dir->esq)<=alt_NO((*raiz)->dir->dir))
					rotacaoRR(raiz);
				else
					rotacaoRL(raiz);
			}
	}
	if(valor>(*raiz)->info){
		if((res=remove_EmementAvl(&(*raiz)->dir,valor))==1)
			if(fatorBalanceamento_no(*raiz)>=2){
				if(alt_NO((*raiz)->esq->dir)<=alt_NO((*raiz)->esq->esq))
					rotacaoLL(raiz);
				else
					rotacaoLR(raiz);
			}
	}
	//-----------------
	if((*raiz)->info==valor){
		if(((*raiz)->esq==NULL || (*raiz)->dir==NULL)){
			struct NO *outroNo=(*raiz);
			if((*raiz)->esq!=NULL)
				*raiz=(*raiz)->esq;
			else
				*raiz=(*raiz)->dir;
			free(outroNo);
		}
		else{
			struct NO *temp=procuraMenor((*raiz)->dir);
			(*raiz)->info=temp->info;
			remove_EmementAvl(&(*raiz)->dir,(*raiz)->info);
			if(fatorBalanceamento_no(*raiz)>=2){
				if(alt_NO((*raiz)->esq->dir)<=alt_NO((*raiz)->esq->esq))
					rotacaoLL(raiz);
				else
					rotacaoLR(raiz);
			}
		}
		return 1;
		
	}
	return res;
}
//vai ser o da primeira unidade
