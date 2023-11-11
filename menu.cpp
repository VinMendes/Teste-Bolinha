#include <iostream>
#include <string.h>
#include <iomanip>
#include <math.h>
#include <windows.h>
#include <sys\timeb.h>//teste tempo
typedef struct {//teste tempo
    char apelido[10];//teste tempo
    int tempo;//teste tempo
}jogador;//teste tempo
typedef jogador elemento_lista;//teste tempo
#include "listaligada.h"//teste tempo


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

int validar_dificil (Tubo T[], int o, int d) {
    stack_element v1 = peek(T[o].pilha);
    stack_element v2;
    if (T[d].numero_elementos > 0) {
        v2 = peek(T[d].pilha); 
    }
    if (T[o].numero_elementos > 0 && T[d].numero_elementos < TAM-1) {
        if(T[d].numero_elementos == 0) {
            return 1;
        }
        else if(v1 == v2) {
            return 1;
        }
        else {
            return 0;
        }
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
                return -1;
            }
            O--;
        }while(O < 0 || O > 5);

        do{
            cout<<"DESTINO <1 a 6 (-1 para sair)>: ";
            cin>>D;
            if(D == -1) {
                return -1;
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

int jogada_dificil(Tubo T[]){
    stack_element v;
    int O, D;
    int fim = 1;
    int jogada_validada = 0;
    do{

        do{
            cout<<"ORIGEM <1 a 6 (-1 para sair)>: ";
            cin>>O;
            if(O == -1) {
                return -1;
            }
            O--;
        }while(O < 0 || O > 5);

        do{
            cout<<"DESTINO <1 a 6 (-1 para sair)>: ";
            cin>>D;
            if(D == -1) {
                return -1;
            }
            D--;
        }while(D < 0 || D > 5);
        jogada_validada = validar_dificil(T, O, D);

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

int menu() {
    int opcao;
    do {
        system("cls");
        cout<<"Jogo da Bolinha\n\n";
        cout<<"1- Modo Facil \n2- Modo Dificil \n3- Sair";
        cout<<"\n\nQual modo deseja jogar: ";
        cin>>opcao;
    }while(opcao < 1 || opcao > 3);
    return opcao;
}

//teste tempo
void gravar_recordes(Lista& l, int tempo){
    int c, i = 1;
    elemento_lista v, v2;

    c = compr(l);

    cin.ignore();
    cout<<"\nDigite seu apelido: ";
    cin.getline(v.apelido, 10);
    v.tempo = tempo;

    if(c == 0){
        inserir(l, v, i);
    }else{
        for (i=1 ; i<=c ; i++){
            v2 = consultar(l, i);          
            if(v.tempo < v2.tempo){
                inserir(l, v, i);
                return;
            }
        }
        inserir(l, v, i);
    }

    
};
//teste tempo
void imprimir_recordes(Lista& l){
    int c = compr(l);
    elemento_lista v;

    system("cls");
    cout<<" "<<setw(50)<<"\n*** Melhores jogadores ***\n";
    cout<<setw(20)<<"JOGADOR"<<setw(10)<<"TEMPO"<<"\n";
    for (int i=1 ; i<=c ; i++){
        v = consultar(l,i);
        cout<<setw(20)<<v.apelido<<setw(10)<<v.tempo<<" minutos\n";
    }
    cout<<endl;
}


void facil(Tubo T[], Lista& l) {
    int repetir = 1, retorno;

    do{
        iniciar_vazias(T);
        distribuir(T);
        mostrar(T);

        timeb inicio_tempo_jogo, fim_tempo_jogo;//teste tempo
        int total_tempo_jogo; //teste tempo
        ftime(&inicio_tempo_jogo);//teste tempo

        do{
            retorno = jogada(T);
            mostrar(T);
            if(retorno == 0)break;
            if(retorno == -1)break;
        }while(retorno != 0 || retorno != -1);
        system("cls");
        if(retorno == 0) {
            mostrar(T);
            cout<<"\n P A R A B E N S ! ! !";

            //teste tempo
            ftime(&fim_tempo_jogo);
            total_tempo_jogo = 1000.0 * (fim_tempo_jogo.time - inicio_tempo_jogo.time) + (fim_tempo_jogo.millitm -inicio_tempo_jogo.millitm);
            total_tempo_jogo = total_tempo_jogo / (1000 * 60);
            cout << "\nVoce gastou " << total_tempo_jogo << " minutos para resolver!!!";
            gravar_recordes(l, total_tempo_jogo);
            imprimir_recordes(l);

        }
        else {
            cout<<"Nao foi desta vez";
        }
        cout<<"\n Jogar Novamente? 1 (sim) ou 0 (nao): ";cin>> repetir;
        system("cls");
    }while(repetir);
    cout<<"Fim do JOGO"<<endl;
}

void dificil(Tubo T[]) {
    int repetir = 1, retorno;
    do{
        iniciar_vazias(T);
        distribuir(T);
        mostrar(T);
        do{
            retorno = jogada_dificil(T);
            mostrar(T);
            if(retorno == 0)break;
            if(retorno == -1)break;
        }while(retorno != 0 || retorno != -1);
        system("cls");
        if(retorno == 0) {
            mostrar(T);
            cout<<"\n P A R A B E N S ! ! !";
        }
        else {
            cout<<"Nao foi desta vez";
        }
        cout<<"\n Jogar Novamente? 1 (sim) ou 0 (nao): ";cin>> repetir;
    }while(repetir);
    cout<<"Fim do JOGO"<<endl;
}


int main() {
    Tubo T[TAM];
    Lista recordes; //teste tempo
    
    int opcao;

    init(recordes); //teste tempo

    do {
        opcao=menu();
        switch (opcao)
        {
        case 1:
            system("cls");
            facil(T, recordes);// teste tempo
            break;
        
        case 2:
            system("cls");
            dificil(T);
            break;
        case 3:
            system("cls");
            cout<<"Obrigado por jogar nosso jogo";
            break;
        }
    }while(opcao!= 3);
}