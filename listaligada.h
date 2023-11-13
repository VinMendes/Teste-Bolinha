#ifndef LISTALIGADA_H_INCLUDED
#define LISTALIGADA_H_INCLUDED

//
//  
////  Created by  Engelbrecht on 13/03/19.
//  Copyright � 2019 Angela Engelbrecht. All rights reserved.
//
// ListaLinearDinamica.h
// -------------------------------------------------------------------------
// esta biblioteca foi construida exclusivamente para teste dos exercicios
// nao altere o seu conteudo (nao modifique seu conteudo e nem faca insercoes).
// considere como uma biblioteca fechada.
// -------------------------------------------------------------------------
// para o desenvolvimento das operacoes foi utilizada a representacao por
// alocacao dinamica
// -------------------------------------------------------------------------



#include <iostream>
#include <stdlib.h>
using namespace std;

struct  no  {
    elemento_lista  info ;
    no  *link;
};

struct Lista {
    int comp;
    no *primeiro;
};
///fun��o auxiliar para as mensagens de erros
void  Erro ( int k ){
    switch( k){
        case 1: cout << "  Posicao Invalida"; exit(1);
        case 2: cout << "  Erro de Overflow " ; exit(1);
        case 3: cout  << "  Erro de Underflow "; exit(1);
        default: exit(1);
    }
}
///fun��o para iniciar a lista linear vazia
void  init ( Lista& L){
    L.comp = 0;
    L.primeiro = NULL;
}
///fun��o que testa se a lista linear est� vazia 1 (sim) 0 (n�o)
int   vazia (Lista L){
    if( L.primeiro == NULL)
        return 1;
    else return 0;
}
/// fun��o que retorna o n�mero de elementos na lista linear
int compr(Lista L){
    return L.comp;
}
///fun��o que alocamem�ria para um n�
no* novo_no(){
    no* novo = (no*) malloc (sizeof(no));
    if (!novo) exit(1);
    return novo;
}
///fun��o que insere uma informa��o na I-�sima posi��o
void inserir ( Lista& L, elemento_lista V,  int I){
    no *p, *x, *s=NULL;   int  cont = 1;
    if (( I <= 0 ) || ( I > L.comp + 1)) Erro (1);
    p= novo_no();
    p->info = V;
    x = L.primeiro;
    while(  (cont < I ) && ( x != NULL)) {
        s = x;
        x =x->link ;
        cont ++;
    }
    if ( x == L. primeiro)   L. primeiro = p;
    else  s->link  = p;
    p-> link  = x;
    L.comp++;
}
///fun��o que consulta uma informa��o da I-�sima posi��o
elemento_lista consultar (Lista L, int I){
    no * x;
    if (( I <= 0 ) || ( I > L.comp ))   Erro (1);
    int  cont = 1;
    x = L.primeiro;
    while((cont < I ) && ( x!=NULL))
    {
        x =x->link ;
        cont ++;
    }
    return x->info;
}
///fun��o que altera a informa��o da I-�sima posi��o
void alterar (Lista& L, elemento_lista V, int I){
    no * x; int  cont = 1;
    if (( I <= 0 ) || ( I > L.comp ))   Erro (1);
    x = L. primeiro;
    while((cont < I ) && ( x!=NULL))
    {
        x =x->link ;
        cont ++;
    }
    x->info= V;
}
///fun��o que insere uma informa��o na I-�sima posi��o
elemento_lista eliminar (Lista& L, int I){
    elemento_lista V;
    no * x, *s=NULL;
    if (( I <= 0 ) || ( I > L.comp ))   Erro (1);
    int  cont = 1;
    x = L.primeiro;
    while((cont < I ) && ( x!= NULL))    {
        s = x;
        x =x->link ;
        cont ++;
    }
    V =  x->info;
    if( x == L.primeiro)
        L.primeiro = x->link;
    else  s->link = x->link;
    free(x) ;
    L.comp--;
    return V;
}

#endif // LISTALIGADA_H_INCLUDED
