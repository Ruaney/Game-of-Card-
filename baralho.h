#ifndef BARALHO_H_
#define BARALHO_H_

struct tcarta{
  char face[3];
  char naipe;
  int valor;
  char nome[30];
};
typedef struct tcarta Tcarta;

typedef struct nopilha{
  struct tcarta baralho;
  struct nopilha *prox;
}NoPilha;

struct pilha{
  int nCards;
  NoPilha *prim;
};
typedef struct pilha Pilha;
#endif