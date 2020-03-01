#include <stdio.h>
#include <stdlib.h>
#include "tarefas.h"

Pontuacao* inicializaPontuacao(){
    Pontuacao *novo = (Pontuacao*) malloc(sizeof(Pontuacao));
    novo->Ct = novo->Et = novo->Ot = novo->Pt = 0;
    novo->At = 0;//: Antecedência na qual a tarefa foi cumprida;
    novo->Pr = novo->Cr = novo->Er= novo->Or = 0;//: Recursos restantes ao nal do jogo;
    novo->Pn = novo->Cn = novo->En= novo->On = 0;//: Recursos de tarefas não cumpridas;
    return novo;
}

void imprimePontuacao(Pontuacao *p){
    printf("Pt: %d, Ct: %d, Et: %d, Ot %d\n", p->Pt, p->Ct, p->Et, p->Ot );
    printf("At: %d\n", p->At);
    printf("Pr: %d, Cr: %d, Er: %d, Or %d\n", p->Pr, p->Cr, p->Er, p->Or);
    printf("Pn: %d, Cn: %d, En: %d, On %d\n", p->Pn, p->Cn, p->En, p->On);
}

Fila* inicializaFila(){
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}
int vaziaFila(Fila *f){
    return(f->ini == NULL);
}
No* insereTarefasFim(No* fim, Tarefas v){
    No *novo = (No*) malloc(sizeof(No));
    novo->objetivo = v;
    if(fim != NULL)
        fim->prox = novo;
    novo->prox = NULL;
    return novo;   
}
No* retiraTarefaIni(No *ini){
    No *p = ini->prox;
    free(ini);
    return p;
}
Fila* insereFila(Fila *f, Tarefas v){
    f->fim = insereTarefasFim(f->fim, v);
    if(f->ini == NULL){
        f->ini = f->fim;
    }
    return f;
}
void retiraElemento(Fila **f){
    if(vaziaFila(*f)){
        printf("Fila vazia.\n");
        exit(1);
    }
    (*f)->ini = retiraTarefaIni((*f)->ini);
    if((*f)->ini == NULL)
        (*f)->fim == NULL;
}
void imprimeFila(Fila *f,int turno){
    No* q;
    for(q=f->ini;q!=NULL; q=q->prox)
        if (q->objetivo.prazo > 0){
        printf("%2d (P:%d, E:%d, O:%d, C:%d);", q->objetivo.prazo, q->objetivo.paus, q->objetivo.espadas
            ,q->objetivo.ouros, q->objetivo.copas);
        }
}
void decrementoPrazo(Fila **f, Pontuacao *points, int turno){
    No *p;
   for(p = (*f)->ini;p!=NULL; p=p->prox){
        if(p->objetivo.prazo > 0) p->objetivo.prazo--;
        
        if(p->objetivo.prazo == 0){
            printf("tarefa não cumprida\n");
            if((*f)->ini == p){
                incrementaPontuacaoTarNcumprida(points, p->objetivo);
                retiraElemento(f);
            }           
        }       
    }    
}

void cumprirTarefa(Fila *f,Pontuacao *points){
    No *p;
    retiraElemento(&f);
    printf("tarefa cumprida!!\n");
        for(p = f->ini;p!=NULL; p=p->prox){      
            if(p->objetivo.prazo == 0){
                if(f->ini == p){
                    retiraElemento(&f);
                }           
            }       
    }    
}

void incrementaPontuacaoTarNcumprida(Pontuacao *points, Tarefas tar){
    //incrementar as tarefas não cumpridas
    points->Pn += tar.paus;
    points->Cn += tar.copas;
    points->En += tar.espadas;
    points->On += tar.ouros;    
}