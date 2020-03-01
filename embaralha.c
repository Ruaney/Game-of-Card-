#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "embaralha.h"

void *criapilha(){
    Pilha *p = (Pilha *) malloc(sizeof(Pilha));
    p->prim = NULL;
    p->nCards = 0;
    return p;
}

int ehvaziapilha(Pilha **p){
    if ((*p)->prim == NULL) return 1;
    return 0;
}

void inserepilha(Pilha **p, Tcarta t){
    NoPilha *nova = (NoPilha *)malloc(sizeof(NoPilha));
    nova->baralho = t;
    nova->prox = (*p)->prim;
    (*p)->nCards++;
    (*p)->prim = nova;
}

Tcarta removepilha(Pilha **p){
    Tcarta *n;
    NoPilha *descartado = NULL;

    n = (Tcarta*) malloc(sizeof(Tcarta));
	descartado = (*p)->prim;
	(*p)->prim = descartado->prox;
    (*p)->nCards--;
	descartado->prox = NULL;
	n[0] = descartado->baralho;
	free(descartado);
    
	return *n;
}

void imprimePilha(Pilha *p){
    NoPilha *impr = p->prim;
    int C =0, O = 0, P = 0, E=0;
    printf("numero de cartas no monte: %d\n", p->nCards);
    for (impr=p->prim; impr!=NULL; impr=impr->prox){
        printf("Elemento = %s , %c\n", impr->baralho.face , impr->baralho.naipe);
        if(impr->baralho.naipe == 'C') C++;
        if(impr->baralho.naipe == 'O') O++;
        if(impr->baralho.naipe == 'P') P++;
        if(impr->baralho.naipe == 'E') E++;

    }
        
    printf("C: %d\n",C);
    printf("O: %d\n",O);
    printf("P: %d\n",P);
    printf("E: %d\n",E);
}

