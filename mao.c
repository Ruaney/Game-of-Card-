#include <stdio.h>
#include <stdlib.h>

#include "mao.h"

Tcarta removeCarta(Mao **m){
    Tcarta inf;
    Mao *p = *m;

    inf = p->v;
    *m = p->prox; 
    p->prox = NULL;  
    free(p);
    
    return inf;
}

Mao* inicializaMao(){
    return NULL;
}

Mao* insereMao(Mao *m, Tcarta t, int id){
    Mao* novo = (Mao*) malloc(sizeof(Mao));
    novo->ref = id;
    novo->v = t;
    novo->prox = m;
    return novo;
}

int vaziaLista(Mao *m){
    return (m == NULL);
}

void imprimeMao(Mao *m){
    Mao *p;
    printf("\t");
    for(p = m; p!=NULL; p = p->prox){
        printf(" %1s-%c | ",p->v.face, p->v.naipe);       
    }   
}

void imprimeRef(Mao *m){
    Mao *p;  
    for(p=m;p!=NULL;p=p->prox)
        printf(" %5d ",p->ref);
    printf("\n");
}

Recursos *inicializacaorec(){
    Recursos *p = (Recursos*) malloc(sizeof(Recursos));
    p->copas = 0;
    p->espadas = 0;
    p->ouro = 0;
    p->paus = 0;
     return p;
}