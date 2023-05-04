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
        int key(int valor);
        void insere(int valor, string palavra);
        void imprime();
        void recupera(int valor);
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

int tabelaHash::key(int valor){
    return valor%tamanho;
}

void tabelaHash::insere(int valor, string palavra){
    int cadeado= key(valor);
    int i = 0;
    bool verdade = false;
    while(i<4 and !verdade){
        if( tabela[cadeado][i].chave == -1){
            tabela[cadeado][i].chave = valor;
            tabela[cadeado][i].valor = palavra;
            verdade = true;
        }else if(tabela[cadeado][i].chave == valor){
            cout << "ITEM JÁ ESTÁ NA TABELA!"<<endl;
            verdade = true;
        }
        i++;
    }
    if(!verdade)
        cout << "NÚMERO MÁXIMO DE COLISÕES PARA CHAVE!"<<endl;
}

void tabelaHash::imprime(){
    for(unsigned i=0; i<tamanho; i++){
        cout << i << ":";
        for(unsigned k=0; k<4; k++)
            cout << "[" << tabela[i][k].chave << "/" << tabela[i][k].valor << "]";
        cout << endl;
    }
}

void tabelaHash::recupera(int valor){
    int cadeado= key(valor);
    bool verdade = false;
    int i = 0;
    while(i<4 and !verdade){
        if(tabela[cadeado][i].chave ==valor){
            cout << tabela[cadeado][i].valor << endl;
            verdade = true;
        }
        i++;
    }
    if(!verdade)
        cout << "NÃO ENCONTRADO!"<<endl; 
}

int main(){
    unsigned tamanho,dados;
    int valor;
    string palavra;
    cin >> tamanho >> dados;
    tabelaHash hash(tamanho);
    for(unsigned i=0; i<dados; i++){
        cin >> valor >> palavra;
        hash.insere(valor,palavra);
    }
    int procurado;
    for(unsigned i=0;i<4;i++){
        cin >> procurado;
        hash.recupera(procurado);
    }
    hash.imprime();
    return 0;
}
