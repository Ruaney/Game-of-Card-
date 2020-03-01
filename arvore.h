#ifndef ARVORE_H_
#define ARVORE_H_
#include "baralho.h"

typedef struct Tarv{
    int chave;
    void *esq;
    void *dir;
} Tarvore;

Tarvore *CriaArvore();
int ArvoreVazia(Tarvore **arv);
Tarvore *BuscaMenorArvore(Tarvore **arv);
Tarvore *BuscaArvore(Tarvore **arv, int x);
int InsereArvore(Tarvore **arv, int x);
int altura(Tarvore *x);
void ImprimeArvore(Tarvore **arv);
void ImprimeArvorePre(Tarvore **arv);
void ImprimeArvoreIn(Tarvore **arv);
void ImprimeArvorePos(Tarvore **arv);




#endif