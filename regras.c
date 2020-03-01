#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "regras.h"
#include "embaralha.h"

void descarta(Mao *n,int numc, Recursos *rec){
    Mao *p = n;
    int i = 0;
    char c;
    
    while(i<numc){
        c = p->v.naipe;
        switch(c){
        case 'C':
            rec->copas += p->v.valor;
            break;
        case 'E':
            rec->espadas += p->v.valor;
            break;
        case 'O':
            rec->ouro += p->v.valor;
            break;
        default:
            rec->paus += p->v.valor;
        }
        i++;
        if(p->prox != NULL)
            p = p->prox;
    }
   
}
void bonus(Mao *n,int numc, Recursos *rec){
    Mao *p = n;
    Tcarta c[numc];
    int arm, bn, numc2 = numc;
    int aux = 1;
    char resp;
    char np[80]= {"p"};
    int nenhumBonus = 0;
  
    for(int i = 0; i<numc; i++){
        c[i] = p->v;
        if(p->prox == NULL)
            break;
        else
            p = p->prox;    
    }    
    switch (numc2){
        case 5:
            if (c[0].naipe == c[1].naipe && c[0].naipe == c[2].naipe && c[0].naipe == c[3].naipe && c[0].naipe == c[4].naipe){
                printf("Você fez uma sequência de cinco cartas do mesmo naipe e recebeu um bônus de +15!\n");
                bn = 15;
            }else{
                if ((c[4].valor == (c[3].valor + 1) && c[4].valor == (c[2].valor + 2) && c[4].valor == (c[1].valor+3) && c[4].valor == (c[0].valor + 4))
                    || (c[4].valor == (c[3].valor - 1) && c[4].valor == (c[2].valor - 2) && c[4].valor == (c[1].valor - 3) && c[4].valor == (c[0].valor - 4))){
                    printf("Você fez uma sequência de 5 cartas e recebeu um bônus de +10");
                    bn = 10;
                }else{
                    printf("Nenhum bônus fornecido com esse descarte\n");
                    nenhumBonus = 1;
                    break;
                }
            }
            break;  
        case 4:
            if ((c[0].valor  == c[1].valor) && (c[0].valor == c[2].valor) && (c[0].valor == c[3].valor)){
                printf("Você fez uma quadra e recebeu um bônus de +20");
                bn = 20;
            }else{
                if (c[0].naipe == c[1].naipe && c[0].naipe == c[2].naipe && c[0].naipe == c[3].naipe){
                    printf("Você fez uma sequência de quatro cartas do mesmo naipe e recebeu um bônus de +12");
                    bn = 12;
                }
                else{
                    if ((c[3].valor) == (c[2].valor + 1) && (c[3].valor) == (c[1].valor + 2) && (c[3].valor) == (c[0].valor + 3)
                        || (c[3].valor) == (c[2].valor - 1) && (c[3].valor) == (c[1].valor - 2) && (c[3].valor) == (c[0].valor - 3)){
                        printf("Você fez uma sequência de quatro cartas e recebeu um bônus de +8");
                        bn = 8;
                    }else{
                        printf("Nenhum bônus fornecido com esse descarte\n");
                        nenhumBonus = 1;
                    }
                } 
            }
            break;
        case 3:
            if ((c[0].naipe == c[1].naipe ) && (c[0].naipe == c[2].naipe)){
                printf("Você fez uma sequência de três cartas do mesmo naipe e recebeu um bônus de +9");
                bn = 9;
            }else{
                if ((((c[2].valor) == (c[1].valor + 1)) && ((c[2].valor) == (c[0].valor + 2)) ) 
                    || ((c[2].valor) == (c[1].valor - 1)) && ((c[2].valor) == (c[0].valor - 2))){
                    printf("Você fez uma sequência de três cartas e recebeu um bônus de +6");
                    bn = 6;
                }
                else{
                    if(((c[0].valor) == (c[1].valor)) && ((c[0].valor) == (c[2].valor))){
                        printf("Você fez uma trinca e recebeu um bônus de +5");
                        bn = 5;
                    }else{
                        printf("Nenhum bônus fornecido com esse descarte\n");
                        nenhumBonus = 1;   
                    }  
                }
            }
            break;
        case 2:
            if (c[0].naipe == c[1].naipe){
                printf("Você fez um par de duas cartas do mesmo naipe e recebeu um bônus de +6");
                bn = 6;
            }else{
                if ((c[1].valor) == (c[0].valor + 1) || (c[1].valor) == (c[0].valor - 1)){
                    printf("Você fez uma sequência de duas cartas e recebeu um bônus de +4");
                    bn = 4;
                }else{
                    if ((c[0].valor) == (c[1].valor)){
                        printf("Você fez um par e recebeu um bônus de +2");
                        bn = 2;
                    }else{
                        printf("Nenhum bônus fornecido com esse descarte\n");
                        nenhumBonus = 1;
                    }
                }
            }
            break;
        default:
            printf("Nenhum bônus foi fornecido com esse descarte\n");
            nenhumBonus = 1;
            break;
    }
    if(nenhumBonus == 0){
        printf("\nEscolha o naipe em que deseja armazenar o seu bonus:| P | E | O | C |\n");
        scanf(" %s",np);
        
        while(aux == 1){
            if (strcmp(np,"P") == 0 || strcmp(np,"p") == 0){
                printf("Recurso armazenado no nipe Paus\n");
                aux = 0;
                rec->paus = rec->paus + bn;
            }else{
                if (strcmp(np,"E") == 0 || strcmp(np,"e") == 0){
                    printf("Recurso armazenado no nipe Espadas\n");
                    aux = 0;
                    rec->espadas = rec->espadas + bn;
                }else{
                    if (strcmp(np,"O") == 0 || strcmp(np,"o") == 0){
                        printf("Recurso armazenado no nipe Ouro\n");
                        aux = 0;
                        rec->ouro = rec->ouro + bn;
                    }else{
                        if (strcmp(np,"C") == 0 || strcmp(np,"c") == 0){
                            printf("Recurso armazenado no nipe Copas\n");
                            aux = 0;
                            rec->copas = rec->copas + bn;
                        }else{
                            printf("Opção invalida!\n");
                            printf("\nEscolha o naipe em que deseja armazenar o seu bônus:| P | E | O | C |\n");
                            scanf(" %s",np);  
                        }
                    }
                }
            }
        }
    }
}

void trocaCartas(Mao *m1, Mao *m2){
    Tcarta temp;
    temp = m1->v;
    m1->v = m2->v;
    m2->v = temp;
}

Mao* buscaPorRef(Mao *m, int id){
    Mao *p;
    for (p = m; p!=NULL; p=p->prox)
        if(p->ref == id)    
    return p;   
}

Mao* reposicionar(Mao *m){
    Mao *p1, *p2;
    Mao *p = m;
    int n1,n2,j,sn = 0;
    char buffer[80] = {"s"};

    while (1) {
        if (strcmp(buffer,"n") == strigual || strcmp(buffer,"N")  == strigual) {
            printf("Retornando ao menu...\n");
            break;
        }else{
            sn = (strcmp(buffer,"s") == strigual || strcmp(buffer,"S")  == strigual);      
            switch (sn) {
                case verdade:
                    printf("Escolha a primeira posição de 1 a 5: \n");
                    scanf(" %d",&n1);
                    printf("Escolha a segunda posição de 1 a 5: \n");
                    scanf(" %d",&n2);
                    if((n1 > 0 && n1 <= 5) && (n2 >0 && n2 <= 5) ){
                        p1 = buscaPorRef(m, n1);
                        p2 = buscaPorRef(m, n2);
                        if(p1 == NULL|| p2 == NULL) 
                            printf("posição não existe!\n");
                        else
                            trocaCartas(p1, p2);
                    }else
                        printf("Posição inválida.\n");
                    break;
                default:
                    printf("Opção invalida!\n");
                    break;
            }
            printf("\t");
            printf("======================================\n");
            imprimeMao(m);
            printf("\n");
            printf("\t");
            imprimeRef(m);
            printf("\t");
            printf("======================================\n");
            printf("Deseja reposicionar outra cartar? S/N\n");   
            scanf(" %[^\n]s",buffer);
        }
    }
    return m;
}

Mao* preencheMao(Mao *maojogador, Pilha **monte, int numCartasNaMao){ 
    int i=0, k = 0;

    if(numCartasNaMao == 0)
        for(int j = 5; j != 0; j--){
            maojogador = insereMao(maojogador, removepilha(monte), j);
    }else{
        k = 5-numCartasNaMao;
    
        for(int j = k; j != 0; j--){
            maojogador = insereMao(maojogador, removepilha(monte), j);
            
        }   
    }
    return maojogador;
}

int verificaNCartas(Mao* m){
    Mao *p = m; 
    int i = 0 ;
    for(p;p!=NULL;p = p->prox){
        i++;
    }
    return i;
}