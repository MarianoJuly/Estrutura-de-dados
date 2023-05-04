#include <iostream>
using namespace std;

class noh{
    friend class tabelaHash;
    private:
        int chave;
        string valor;
        noh *proximo;
    public:
        noh();
};

noh::noh(){
    chave = -1;
    valor = "";
    proximo = NULL;
}

class tabelaHash{
    private:
        unsigned tamanho;
        noh **tabela;
    public:
        tabelaHash(unsigned tam);
        ~tabelaHash();
        void insere(int key, string val);
        void imprime();
        void recupera(int key);
};

tabelaHash::tabelaHash(unsigned tam){
    tamanho = tam;
    tabela = new noh*[tam];
    for(unsigned i=0; i<tam;i++){
        tabela[i] = new noh[4];
    }
}

tabelaHash::~tabelaHash(){
    for(unsigned i=0; i<tamanho; i++){
        delete[]tabela[i];
    }
    delete[]tabela;
}

void tabelaHash::recupera(int key){
    int h = key % tamanho;
    bool achei = false;
    int i = 0;
    while(i<4 and !achei){
        if(tabela[h][i].chave == key){
            achei = true;
            cout << tabela[h][i].valor << endl;
        }
        i++;
    }
    if(!achei){
        cout << "NÃO ENCONTRADO!\n"; 
    }
}

void tabelaHash::imprime(){
    for(unsigned i=0; i<tamanho; i++){
        cout << i << ":";
        for(unsigned k=0; k<4; k++){
            cout << "[" << tabela[i][k].chave << "/" << tabela[i][k].valor << "]";
        }
        cout << endl;
    }
}

void tabelaHash::insere(int key, string val){
    int h = key % tamanho;
    int i = 0;
    bool coloquei = false;

    while(i<4 and !coloquei){
        if(tabela[h][i].chave == -1){
            tabela[h][i].chave = key;
            tabela[h][i].valor = val;
            coloquei = true;
        }else if(tabela[h][i].chave == key){
            cout << "ITEM JÁ ESTÁ NA TABELA!\n";
            coloquei = true;
        }
        i++;
    }
    if(!coloquei){
        cout << "NÚMERO MÁXIMO DE COLISÕES PARA CHAVE!\n"; 
    }
}

int main(int args, char **argv){
    unsigned tam,qtd;
    int key;
    string val;
    cin >> tam >> qtd;

    tabelaHash hash(tam);
    
    for(unsigned i=0; i<qtd; i++){
        cin >> key >> val;
        hash.insere(key,val);
    }
    for(unsigned i=0;i<4;i++){
        cin >> key;
        hash.recupera(key);
    }

    hash.imprime();
    return 0;
}