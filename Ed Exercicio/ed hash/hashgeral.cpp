#include <iostream>
#include <string>
using namespace std;
class noh{
    friend class lista;
private:
    int chave;
    int valor;
    string posicao;
public:
    noh *proximo;
    noh(int valor, string posicao);
};

noh::noh(int v, string s){
    proximo=NULL;
    valor=v;
    posicao=s;
};

class lista{
private:
    noh *primeiro;
    noh *ultimo;
    const int tamanho=4;
    int quantidade;
public:
    lista();
    void insere(int numero, string frase);
};

lista::lista(){
    primeiro=NULL;
    ultimo=NULL;
    quantidade=0;
}

void lista::insere(int numero, string frase){
    if(quantidade==tamanho){
        cout<<"NÚMERO MÁXIMO DE COLISÕES PARA CHAVE!"<<endl;
    }else{
    noh *novo= new noh(numero, frase);
        if(tamanho==-1){
            primeiro=novo;
            ultimo=novo;
        }else{
            ultimo->proximo=novo;
            ultimo=novo;
            quantidade++;
        }
        quantidade++;
    }   
}

// Um hash guarda vários funcionários, considerando o seu nascimento como chave.
class Hash {
    private:
        int tamanho;
        noh **elementos;
    public:
        Hash(int cap);
        int HashKey(int v);
        ~Hash();
        void Inserir(int a, string b);
};
// === Hash ===================================================================
Hash::Hash(int cap){ // cap tem valor default
    tamanho=cap;
    elementos= new noh*[cap];
    for(int i=0; i<cap; i++){
        elementos[i]=NULL;
    }
}

int Hash::HashKey(int v){
    return v%tamanho;
}

Hash::~Hash() {
    for (int i=0; i < tamanho; i++) {
        noh* atual = elementos[i];

        // percorre a lista removendo todos os nós
        while (atual != NULL) {
            noh* aux = atual;
            atual = atual->proximo;
            delete aux;
        }
    }
    delete[] elementos;
}

void Hash::Inserir(int valoriza, string lugar) {
    int HashValue=HashKey(valoriza);
    lista 
}

// === Programa ===============================================================
int main( ) {
    unsigned qtde;
    cin >> qtde; // quantidade de posições na tabela
    Hash tabela(qtde); // cria uma tabela com 10 endereços
    cin >> qtde; // quantidade de funcionários a inserir
    int valor;
    string dor;
    for (unsigned int i = 0; i < qtde; ++i) {
        cin>>valor>>dor;
        tabela.Inserir(valor, dor);
    }
    Data hoje(dia, mes);
    cout << tabela.QtdeAniversariantes(hoje) << ' '
         << tabela.PorcentagemDeUso() << endl;
    return 0;
}