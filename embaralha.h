#ifndef EMBARALHA_H
#define EMBARALHA_H

#include "baralho.h"

void *criapilha();

int ehvaziapilha(Pilha **p);

void inserepilha(Pilha **p,Tcarta t);

Tcarta removepilha(Pilha **p);

void imprimePilha(Pilha *p);

#endif