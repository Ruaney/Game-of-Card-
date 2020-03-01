#include "mao.h"
#include "tarefas.h"
#define strigual 0
#define verdade 1
#define falso 0

void menu(Mao *m, Pilha *monte, int *utilvector, Fila *f, Fila *tar, Tcarta *cartas, int aux);//Menu principal
void descarta(Mao *n,int numc, Recursos *rec);//descarta as cartas e da a pontuação equivalente a cada carta
void bonus(Mao *n,int numc, Recursos *rec);//Da os bonus de recursos
Mao* buscaPorRef(Mao *m, int id);//Busca a carta na MÃO pela referencia
void trocaCartas(Mao *m1, Mao *m2);//Pega duas referencias e troca as cartas de posiçao a partir da referencia.
Mao* reposicionar(Mao *m);//reposicionar: pega 2 numeros aleatorios de referencia e altera o conteudo dos ponteiros
Mao* preencheMao(Mao *maojogador, Pilha **monte,int numCartasNaMao);
int verificaNCartas(Mao* m);//verifica quantidade de cartas na mao

