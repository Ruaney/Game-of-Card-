#ifndef MAO_H_
#define MAO_H_

#include "baralho.h"

struct recursos{
  int copas;
  int espadas;
  int paus;
  int ouro;
  int reembaralhamento;
};

struct mao{
    int ref;
    struct tcarta v;
    struct mao *prox;
};
typedef struct mao Mao;
typedef struct recursos Recursos;

Mao* inicializaMao();//Inicializa a Mao do jogador retornando NULL

Mao* insereMao(Mao *m, Tcarta t, int id);//inserção no início: retorna a mao atualizada 

void imprimeMao(Mao *m);//função imprime: imprime as 5 cartas(valor e naipe) na mão do jogador

void imprimeRef(Mao *m);//Imprime as referencias(ref) das cartas que estão na mão

int vaziaLista(Mao *m);//função vazia: retorna 1 se vazia ou 0 se não vazia

Recursos *inicializacaorec();//Inicializa os recursos com NULL

Tcarta removeCarta(Mao **m);//remoção sequencial simples




#endif /*MAO_H_*/