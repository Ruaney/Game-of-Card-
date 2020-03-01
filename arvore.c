#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "baralho.h"

Tarvore *CriaArvore(){
	return NULL;
}

int ArvoreVazia(Tarvore **arv){
	if((*arv) == NULL) return 1;
	else return 0;
}

Tarvore *BuscaMenorArvore(Tarvore **arv){
	if(ArvoreVazia(arv)) return NULL;
	if(!ArvoreVazia((Tarvore **)&((*arv)->esq))) 
		return BuscaMenorArvore((Tarvore **)&((*arv)->esq));
	else return (*arv);
}

Tarvore *BuscaArvore(Tarvore **arv, int x){
	if(ArvoreVazia(arv)) return NULL;
	if(x < (*arv)->chave) return BuscaArvore((Tarvore **)&((*arv)->esq),x);
	if(x > (*arv)->chave) return BuscaArvore((Tarvore **)&((*arv)->dir),x);
	if(x == (*arv)->chave) return (*arv);
}

int InsereArvore(Tarvore **arv, int x){
	Tarvore *novo;
	if(ArvoreVazia(arv)) {
		novo = (Tarvore *) malloc(sizeof(Tarvore));
		if(novo == NULL) return 0;
		novo->chave = x;
		novo->esq = NULL;
		novo->dir = NULL;
		(*arv) = novo;
		return 1;
	}
	if(x <= (*arv)->chave) return InsereArvore((Tarvore **)&((*arv)->esq),x);
	if(x > (*arv)->chave) return InsereArvore((Tarvore **)&((*arv)->dir),x);
}

int altura(Tarvore *x){
    int alesq, aldir;
    if(ArvoreVazia(&x)) return 0;
    else{
        alesq = 1 + altura(x->esq);
        aldir =1 + altura(x->dir);
        if(alesq < aldir) return (alesq);
        else return (aldir);
    }
}

void ImprimeArvore(Tarvore **arv){
	printf("InOrdem:  ");
	ImprimeArvoreIn(arv);
	printf("\n");
	printf("PreOrdem: ");
	ImprimeArvorePre(arv);
	printf("\n");
	printf("PosOrdem: ");
	ImprimeArvorePos(arv);
	printf("\n");
}
void ImprimeArvorePre(Tarvore **arv){
	if(ArvoreVazia(arv)) return;
	printf("| %3d ",(*arv)->chave);
	ImprimeArvorePre((Tarvore **)&((*arv)->esq));
	ImprimeArvorePre((Tarvore **)&((*arv)->dir));
}

void ImprimeArvoreIn(Tarvore **arv){
	if(ArvoreVazia(arv)) return;
	ImprimeArvoreIn((Tarvore **)&((*arv)->esq));
	printf("| %3d ",(*arv)->chave);
	ImprimeArvoreIn((Tarvore **)&((*arv)->dir));
}
void ImprimeArvorePos(Tarvore **arv){
	if(ArvoreVazia(arv)) return;
	ImprimeArvorePos((Tarvore **)&((*arv)->esq));
	ImprimeArvorePos((Tarvore **)&((*arv)->dir));
	printf("| %3d ",(*arv)->chave);
}
