#include <iostream>
#include <string.h>
#include <iomanip>
#include <math.h>
#include <windows.h>

#define TAM 6
using namespace std;

typedef int stack_element;
#include "stack.h"

typedef struct {
    int numero_elementos;
    Stack pilha;
} Tubo;

void distribuir(Tubo T[]){
    int num ;

    srand(time(0));

    for(int i=0 ; i<=(TAM-1) ; i++){
        num = (rand()%(TAM-1)) + 1;
        push(T[i].pilha, num);
    }
}

void mudacor(int cor) {
    /*
    0 = Preto           8 = Cinza
    1 = Azul            9 = Azul Claro
    2 = Verde           A = Verde Claro
    3 = Verde-Aguia     B = Verde-Aguia Claro
    4 = Vermelho        C = Vermelho Claro
    5 = Roxo            D = Lilas
    6 = Amarelo         E = Amarelo Claro
    7 = Branco          F = Branco Brilhante
    */
}

void printa_cor(int I) {
    int cor[5]={9,13,2,15,6};
    mudacor(cor[I-1]);
    cout<<'O';
    mudacor(15);
}

void iniciar_vazias(Tubo T[]) {
    for(int ax=0; ax<TAM; ax++) {
        initStack(T[ax].pilha);
        T[ax].numero_elementos=0;
    }
}


int main(){
    Tubo T [TAM];
    stack_element v;

    iniciar_vazias(T);

    distribuir(T);

    v = pop(T[0].pilha);

    cout<<"\nimprimindo valor";
    cout<<v;


    /*
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
    return;*/
}
