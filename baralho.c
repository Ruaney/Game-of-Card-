#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "mao.h"
#include "tarefas.h"
#include "embaralha.h"
#include "baralho.h"
#include "regras.h"
#include "arvore.h"

#define N 52
int tari;

void main(void){
    int utilvector[N];  
    Tcarta cartas[N];
    Tarefas tar;
    Mao *maojogador;
    Fila *filaTarefas, *noTar; 
    Pilha *monte;
    int r, r2, numCartasNaMao = 0;
    FILE *baralho;
    FILE *tarefas;
    int i = 0 ,id = 0, j = 0, aux = 0;

    baralho = fopen("Lista_Cartas","r"); 
    tarefas = fopen("tarefasF.txt","r");

    while (!feof(baralho)){
        fscanf(baralho,"%s %c %d %[^\n]s",cartas[i].face,&cartas[i].naipe,&cartas[i].valor,cartas[i].nome);
        utilvector[i] = 0;
        i++;

    }fclose(baralho);
        monte = criapilha();
        srand(time(NULL));
        for(j = N; j != 0; j--){
            id = rand() %N;
            if (utilvector[id]==1)
            j++;
            else{
                inserepilha(&monte, cartas[id]);
                utilvector[id] = 1;
            } 
        }
        
    i = 0;

    if(tarefas == NULL)
        printf("nao foi possivel abrir o arquivo\n");
    filaTarefas = inicializaFila();
    noTar = inicializaFila();
    printf("a\n");
    while (!feof(tarefas)){
        fscanf(tarefas,"%d %d %d %d %d %d %d\n",&tar.turnoAP, &tar.prazo, &tar.paus, &tar.espadas, &tar.ouros,
        &tar.copas, &tar.reembaralhamento);
        noTar = insereFila(noTar, tar);
        i++;
    }tari = i;

    maojogador = inicializaMao();

    maojogador = preencheMao(maojogador, &monte, numCartasNaMao); 
    
    for(No *q = noTar->ini; q!=NULL; q= q->prox){
        if(q->objetivo.turnoAP == 1){
            filaTarefas = insereFila(filaTarefas, q->objetivo);
        }
        aux = q->objetivo.turnoAP;
    }
    fclose(tarefas);
    menu(maojogador,monte, utilvector, filaTarefas, noTar, cartas, aux);
    
}
void menu(Mao *m, Pilha *monte, int *utilvector, Fila *f, Fila *tar, Tcarta *cartas, int aux){ 
    int PF = 0 ,i = 0,r = 0, r2 = 0, numCartasNaMao = 0, turnos = 1, precisaQCarta = 0; 
    Pilha *descarte;
    descarte = criapilha();
    Recursos *recurso;
    recurso = inicializacaorec();
    Tarvore *arv;
    arv = CriaArvore();
    Pontuacao *ponts;
    ponts = inicializaPontuacao();
    
    while(1){
        if(vaziaFila(f) && turnos >= aux){
            ponts->Pr += recurso->paus;
            ponts->Cr += recurso->copas;
            ponts->Er += recurso->espadas;
            ponts->Or += recurso->ouro; 
            PF = altura(arv)*((((ponts->Pr + ponts->Cr +ponts->Er + ponts->Or)/2) 
                + ((ponts->Pt + ponts->Ct + ponts->Et + ponts->Ot)*ponts->At))
                -(ponts->Pn + ponts->Cn +ponts->En + ponts->On));
            printf("A sua pontuação final foi: %d\n",PF);
            break;
        }
        
        printf("P: %d - E: %d - O: %d - C: %d - *:%d\n\n",recurso->paus,recurso->espadas,recurso->ouro,recurso->copas, recurso->reembaralhamento);
        printf("turno: %d\n", turnos);
        printf("tarefas: ");

        imprimeFila(f,turnos);
        
        numCartasNaMao = verificaNCartas(m);  

        printf("\n\t\nMonte (%d)", monte->nCards); printf("\t\t\t\t"); printf("\tDescarte: (%d)", descarte->nCards); 

        printf("\n\n\n");
        imprimeMao(m);
        printf("\n mao: ");
        imprimeRef(m);
        
        printf("\nMenu:\n\n");

        printf("1 -- Reposicionar carta\n");
        printf("2 -- Descartar cartas\n");
        printf("3 -- Cumprir Tarefa \n");
        printf("4 -- Reembaralhar tudo (*:%d)\n",  recurso->reembaralhamento);
        printf("5 -- Finalizar Turno\n");
        printf("Digite opção desejada: \n");
        scanf(" %d", &r);
        
        switch (r){
        case 1:
            if(numCartasNaMao < 2){
                printf("Erro! não é possivel reposicionar cartas, pois não tem cartas suficientes\n");
            }else
                m = reposicionar(m);
            break;
        case 2:
            printf("Deseja descartar quantas cartas?\n");
            scanf(" %d", &r2);
            if(r2 > 0 && r2 <= 5 ){
                if(r2 <= numCartasNaMao){
                    printf("descartando...\n");        
                    descarta(m,r2,recurso);           
                    bonus(m,r2,recurso);
                    int f = 0;
                    Tcarta temp;
                    while(f != r2){
                        temp = removeCarta(&m);
                        inserepilha(&descarte, temp);
                        InsereArvore(&arv,temp.valor);
                        f++;
                    }
                    printf("\n");
                }else{
                    printf("Erro! Você quer remover mais cartas do que tem.\n");
                }
            }
            else
                printf("Erro! Por favor escolha um numero de 1 a 5\n");
            break;
        case 3:
            if(f->ini == NULL){
                printf("sem tarefas para cumprir\n");
                break;
            }
            if(recurso->paus >= f->ini->objetivo.paus)
                if(recurso->espadas >= f->ini->objetivo.espadas)
                    if(recurso->ouro >= f->ini->objetivo.ouros)
                        if(recurso->copas >= f->ini->objetivo.copas){
                            Tarefas auxTar = f->ini->objetivo;
                            if(auxTar.reembaralhamento>0)
                                printf("Você ganhou %d bônus de reembaralhamneto!\n", auxTar.reembaralhamento);
                            cumprirTarefa(f,ponts);
                            recurso->paus -= auxTar.paus;
                            recurso->espadas -= auxTar.espadas;
                            recurso->ouro -= auxTar.ouros;
                            recurso->copas -= auxTar.copas;
                            recurso->reembaralhamento += auxTar.reembaralhamento;
                            ponts->Pt += auxTar.paus;
                            ponts->Ct += auxTar.copas;
                            ponts->Et += auxTar.espadas;
                            ponts->Ot += auxTar.ouros;
                            ponts->At += auxTar.prazo;
                        }
            else
                printf("Recursos insuficientes de Copas!\n");
                else
                    printf("Recursos insuficientes de Ouros!\n");
                    else
                        printf("Recursos insuficientes de Espadas!\n");
                        else
                            printf("Recursos insuficientes de Paus!\n");
            break;
        case 4:
            srand(time(NULL));

            if(recurso->reembaralhamento > 0){
                i = 0;
                printf("Juntando todas as cartas!\n");
                while (i < numCartasNaMao){
                    removeCarta(&m);
                    i++; 
                }

                while (!ehvaziapilha(&monte)){
                    removepilha(&monte);
                }

                while (!ehvaziapilha(&descarte)){
                    removepilha(&descarte); 
                }
                recurso->reembaralhamento--;
                
                printf("Reembaralhando...\n");
            
                for(i = 0; i < N; i++)
                    utilvector[i] = 0;

                for(int j = N; j != 0; j--){
                    int id = rand() %N;
                    if (utilvector[id]==1)
                        j++;
                    else{
                        inserepilha(&monte, cartas[id]);
                        utilvector[id] = 1;
                    }
                    
                } 
                m = preencheMao(m, &monte, 0);    
            }else{
                printf("recursos de reembaralhamento insuficiente\n");
            }
            break;
        case 5:
            precisaQCarta = 5 - numCartasNaMao;
            if(numCartasNaMao == 5){
                printf("mão cheia!\n");
            }else if(ehvaziapilha(&monte) || monte->nCards < precisaQCarta){
                if(recurso->reembaralhamento == 0){
                    ponts->Pr += recurso->paus;
                    ponts->Cr += recurso->copas;
                    ponts->Er += recurso->espadas;
                    ponts->Or += recurso->ouro; 
                    PF = altura(arv)*((((ponts->Pr + ponts->Cr +ponts->Er + ponts->Or)/2) 
                        + ((ponts->Pt + ponts->Ct + ponts->Et + ponts->Ot)*ponts->At))
                        -(ponts->Pn + ponts->Cn +ponts->En + ponts->On));
                    printf("Jogador não possui mais reembaralhamentos e seu monte está insuficiente!\n");
                    printf("A sua pontuação final foi: %d\n",PF);
                    exit(0);
                }else
                    printf("Monte vazio ou o numero de cartas que tem no monte não é suficiente para preencher a mão.\nUse o Reembaralhamento para preenchelo\n");
                break;
            }else{
                printf("preenchendo cartas...\n");
                m = preencheMao(m, &monte, numCartasNaMao);
            }
            turnos++;
            decrementoPrazo(&f, ponts, turnos);

            for(No *q = tar->ini; q != NULL; q= q->prox){
                if(q->objetivo.turnoAP == turnos){
                    f = insereFila(f, q->objetivo);
                } 
            }
            break;
        default:
            printf("Por favor escolha uma opção valida\n");
            break;
        }
        printf("\n======================================\n");
    }  
}