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
    int num, num_elementos;
    int vetor_freq[(TAM)] = {0};
    srand(time(0));

    for(int i=0 ; i<(TAM-1) ; i++){
        num_elementos = 0;
        for(int j=0 ; j<(TAM-1) ; j++){
            
            do{
                num = (rand()%(TAM-1)) + 1;
            }while(vetor_freq[num] >= (TAM-1));

            vetor_freq[num]++;
            push(T[i].pilha, num);
            num_elementos ++;
        }
        T[i].numero_elementos = num_elementos;
    }
}

void mostrar (Tubo T[]){
    Stack P_ax;
    stack_element v, v2;
    for (int ax = 0; ax < TAM-1;ax++) {
        for (int ax2 = 0; ax2 < TAM; ax2++) {
            if(isEmpty(T[ax2].pilha)) {
                cout<<"|   | ";
            }
            else {
                v2=pop(T[ax2].pilha);
                cout<<"| "<<v2<<" | ";
            }
        }
        cout<<endl;
    }
}

int validar (Tubo T[], int o, int d) {
    stack_element v, v2;
    if (T[d].numero_elementos < TAM && T[o].numero_elementos > 0) {
        v = pop(T[o].pilha);
        T[o].numero_elementos--;
        push(T[d].pilha, v);
        T[d].numero_elementos++;
        return 1;
    }
    else {
        return 0;
    }
}
/*
int validar_fim(Tubo T[]) {
    Tubo axi;
    int vazio;
    stack_element V, V2;
    for(int ax = 0; ax <= TAM; ax++) {
        axi = T[ax];
        vazio = isEmpty(axi.pilha);
        if (vazio == 0 && axi.numero_elementos == 5) {
            V = peek(axi.pilha);
            for(int ax2 = 0; ax2 )
            V2 = pop(axi.pilha);

        }

    }
}
*/
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

    HANDLE saida;
    saida = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(saida, cor);
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
    v = pop(T[2].pilha);
    T[2].numero_elementos-1;
    mostrar(T); 


    //v = pop(T[0].pilha);




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
