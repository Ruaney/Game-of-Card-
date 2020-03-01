#ifndef TAREFAS_H_ 
#define TAREFAS_H_

typedef struct pont{
    int Pt, Ct, Et, Ot;
    int At;//: Antecedência na qual a tarefa foi cumprida;
    int Pr, Cr, Er, Or;//: Recursos restantes ao nal do jogo;
    int Pn, Cn, En, On;
}Pontuacao;

typedef struct tarefas{
    int turnoAP;
    int prazo;
    int paus;
    int espadas;
    int ouros;
    int copas;
    int reembaralhamento;
}Tarefas;

struct no{
    Tarefas objetivo;
    struct no *prox;
};
typedef struct no No;

typedef struct fila{
    No *ini;
    No *fim;
}Fila;

/*aloca espaço pra fila e aponta os No para NULL*/
Fila* inicializaFila();
/*auxilia a função insereFila*/
No* insereTarefasFim(No* fim, Tarefas v);
/*Verifica se a FILA está vazia!*/
int vaziaFila(Fila *f);
/*auxilia a função retiraElemento*/
No* retiraTarefaIni(No *ini);
/*passa o endereço do fim pro servo*/
Fila* insereFila(Fila *f, Tarefas v);
/*passa o endereço do ini pro servo*/
void retiraElemento(Fila **f);

void imprimeFila(Fila *f, int turno);

void decrementoPrazo(Fila **f, Pontuacao *points, int turno);

void cumprirTarefa(Fila *f,Pontuacao *points);
Pontuacao* inicializaPontuacao();
void imprimePontuacao(Pontuacao *p);
void incrementaPontuacaoTarNcumprida(Pontuacao *points,Tarefas tar);
#endif /*TAREFAS_H_*/