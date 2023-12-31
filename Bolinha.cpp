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

void iniciar_vazias(Tubo T[]) {
    for(int ax=0; ax<TAM; ax++) {
        initStack(T[ax].pilha);
        T[ax].numero_elementos=0;
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

void mostrar(Tubo T[]) {
    stack_element V;
    Tubo T_ax[TAM];
    iniciar_vazias(T_ax);
    for (int ax = 5; ax >= 1; ax--) {
        for (int ax2 = 0; ax2 < TAM; ax2++) {
            if (T[ax2].numero_elementos == ax) {
                V = pop(T[ax2].pilha);
                T[ax2].numero_elementos--;
                cout<<"| ";
                printa_cor(V);
                cout<< " | ";
                push(T_ax[ax2].pilha, V);
                T_ax[ax2].numero_elementos++;
            }
            else {
                cout << "|   | ";
            }
        }
        cout<<endl;
    }
    for (int ax = 0; ax < TAM; ax++) {
        cout<<"-----"<<" ";
    }
    cout<<endl;
    for (int ax = 0; ax < TAM; ax++) {
        cout<<"  "<<ax+1<<"  "<<" ";
    }
    for (int ax = 5; ax >= 1; ax--) {
        for (int ax2 = 0; ax2 < TAM; ax2++) {
            if (T_ax[ax2].numero_elementos == ax) {
                V = pop(T_ax[ax2].pilha);
                T_ax[ax2].numero_elementos--;
                push(T[ax2].pilha, V);
                T[ax2].numero_elementos++;
            }
        }
        cout<<endl;
    }
}


int validar (Tubo T[], int o, int d) {
    if (T[o].numero_elementos > 0 && T[d].numero_elementos < TAM-1) {
        return 1;
    }
    else {
        return 0;
    }
}


int validar_fim(Tubo T[]) {
    Tubo T_aux[TAM];
    iniciar_vazias(T_aux);
    stack_element v, v_ax;
    int retornar = 0;
    for(int ax = 0; ax < TAM; ax++) {
        if(T[ax].numero_elementos == 5 || T[ax].numero_elementos == 0) {
            if (T[ax].numero_elementos == 5) {
                v_ax=peek(T[ax].pilha);
                for(int ax2 = 5; ax2 > 0; ax2--) {
                    v=pop(T[ax].pilha);
                    T[ax].numero_elementos--;
                    push(T_aux[ax].pilha, v);
                    T_aux[ax].numero_elementos++;
                    if(v_ax != v) {
                        retornar = 1;
                    }
                }
            }
        }
        else {
            retornar = 1;
        }
    }
    for(int ax = 0; ax < TAM; ax++) {
        if(T_aux[ax].numero_elementos > 0) {
            for (int ax2 = T_aux[ax].numero_elementos; ax2 > 0; ax2--) {
                v = pop(T_aux[ax].pilha);
                T_aux[ax].numero_elementos--;
                push(T[ax].pilha, v);
                T[ax].numero_elementos++;
            }
        }
    }

    return retornar;
}

int jogada(Tubo T[]){
    stack_element v;
    int O, D;
    int fim = 1;
    int jogada_validada = 0;
    
    do{

        do{
            cout<<"ORIGEM <1 a 6 (-1 para sair)>: ";
            cin>>O;
            if(O == -1) {
                exit(0);
            }
            O--;
        }while(O < 0 || O > 5);

        do{
            cout<<"DESTINO <1 a 6 (-1 para sair)>: ";
            cin>>D;
            if(D == -1) {
                exit(0);
            }
            D--;
        }while(D < 0 || D > 5);
        jogada_validada = validar(T, O, D);

        if(jogada_validada == 1){
            v = pop(T[O].pilha);
            T[O].numero_elementos--;
            push(T[D].pilha, v);
            T[D].numero_elementos++;
            system("cls");
        }
        if(jogada_validada == 0) {
            cout<<"Jogada invalida\n\n";
            system("pause");
            system("cls");
            mostrar(T);
        }

    }while(jogada_validada == 0);

    
    fim = validar_fim(T);


    return fim;
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
        system("cls");
        mostrar(T);
        cout<<"\n P A R A B E N S ! ! !";
        cout<<"\n Jogar Novamente? 1 (sim) ou 0 (nao): ";cin>> repetir;
    }while(repetir);
    cout<<"Fim do JOGO"<<endl;
    return 0;
}
