#include <iostream>
#include <string>

using namespace std;

const int TAM = 300;

class ListaEstatica {
private:
    string linhas[TAM];
    int tamanho;

public:
    ListaEstatica() {
        tamanho = 0;
    }

    bool listaCheia() {
        return tamanho == TAM;
    }

    void inserir(string linha) {
        if (!listaCheia()) {
            linhas[tamanho] = linha;
            tamanho++;
        }
    }

    string getLinha(int pos) {
        return linhas[pos];
    }
};

struct No {
    string funcao;
    int posicao;
    No* proximo;
};

class PilhaDinamica {
private:
    No* topo;

public:
    PilhaDinamica() {
        topo = nullptr;
    };

    bool pilhaVazia() {
        return topo == nullptr;
    }

    void empilhar(string func, int pos) {
        No* auxiliar = new No;
        auxiliar->funcao = func;
        auxiliar->posicao = pos;
        auxiliar->proximo = topo;
        topo = auxiliar;
    }

    void desempilhar() {
        if (!pilhaVazia()) {
            No* auxiliar = topo;
            topo = topo->proximo;
            delete auxiliar;
        }
    }

    string getFuncao() {
        return topo->funcao;
    }

    int getPosicao() {
        return topo->posicao;
    }

    void incrementarPosicao() {
        topo->posicao += 1;
    }
};

int buscaSequencialFuncoes(string linha, ListaEstatica lista) {
    int i = 0;
    while (i < TAM && linha != lista.getLinha(i).substr(0, 3)) {
        i++;
    }
    return i;
}

int main() {
    ListaEstatica lista;
    PilhaDinamica pilha;

    cout << "+-----= Programa Nee =-----+" << endl;

    bool lendo = true;
    while (lendo) {
        string linha;
        getline(cin, linha);
        lista.inserir(linha);

        if (linha.compare("~") == 0) {
            cout << "teste" << endl;
            lendo = false;
            // break; // Não é necessário mais, pois já temos "lendo = false;"
        }
    }

    int posicaoInicial = buscaSequencialFuncoes("Z :", lista);
    if (posicaoInicial < TAM) {
        pilha.empilhar("Z", posicaoInicial);
    }

    while (!pilha.pilhaVazia()) {
        int posicaoAtual = pilha.getPosicao();
        string linhaLida = lista.getLinha(posicaoAtual);
        
        if (linhaLida.substr(1, 5).compare("PRINT") == 0) {
            cout << linhaLida.substr(6, 2);
            pilha.incrementarPosicao();
        } else if (linhaLida.empty()) {
            pilha.desempilhar();
        } else {
            int novaPosicao = buscaSequencialFuncoes(linhaLida.substr(0, 3), lista);
            if (novaPosicao < TAM) {
                pilha.empilhar(linhaLida.substr(0, 3), novaPosicao);
            } else {
                pilha.desempilhar();
            }
        }
    }

    return 0;
}
