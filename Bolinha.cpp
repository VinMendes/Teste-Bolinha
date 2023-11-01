#include <iostream>
#include <string.h>
#include <iomanip>
#include <math.h>



#define TAM 6

using namespace std;

typedef int stack_element;

#include "stack.h"

typedef struct {
    int numero_elementos;
    Stack pilha;
} Tubo;


void iniciar_vazias(Tubo T[]){


    for (int i=1 ; i<=(TAM-1) ; i++);
};

int main(){
    Tubo T [TAM];
    int repetir = 1, retorno;
    do{
        iniciar_vazias(T);
        distribuir(T);
        mostrar(T);
        do{
            retorno = jogada(T);
            mostrar(T);
            if(retorno == 0)break;
        }while(retorno);
        mostrar(T);
        cout<<"\n P A R A B E N S ! ! !";
        cout<<"\n Jogar Novamente? 1(sim) ou 0(nao): ";cin>> repetir;
    }while(repetir);
    cout<<"Fim do JOGO"<<endl;
    return;
}
