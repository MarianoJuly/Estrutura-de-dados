#include <iostream>
#include <cstdlib>
using namespace std;

typedef int Dado;

class noh{
    friend class lista;
private:
    const Dado dado;
    noh *proximo;
public:
 noh(Dado d=0);
};

noh::noh(Dado d):dado(d){
    proximo= NULL;
};

class lista{
private:
    noh *primeiro;
    noh *ultimo;
    int tamanho;
    void removeTodos();
    void imprimeReverso(noh *umNoh);
public:
    lista();
    lista(const lista& umaLista);
    ~lista();
    inline void insere(Dado dado);
    void insereNoFim(Dado dado);
    void insereNoInicio(Dado dado);
    void insereNaPosicao(int posicao, Dado dado);
    int procura(Dado valor);
    void imprime();
    void imprimeReverso();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};

lista::lista(){
    primeiro=NULL;
    ultimo=NULL;
    tamanho=0;
}

lista::lista(const lista& umaLista){
    tamanho=0;
    primeiro=NULL;
    ultimo=NULL;
    noh *aux= umaLista.primeiro;
    while(aux!=NULL){
        insereNoFim(aux->dado);
        aux->proximo;
    }
}

lista::~lista(){
    removeTodos();
}

void lista::removeTodos(){
    noh *aux=primeiro;
    noh *temp;

    while(aux!=NULL){
        temp=aux;
        aux=aux->proximo;
        delete temp;  
    } 
    tamanho=0;
    primeiro=NULL;
    ultimo=NULL;
}

lista& lista::operator=(const lista& umaLista){ //sobrecarga de operador de atribuição que limpa a lista atual
    removeTodos();
    noh* aux=umaLista.primeiro;

    while(aux!=NULL){
        insereNoFim(aux->dado);
        aux = aux->proximo;
    }
    return *this;
}

void lista::insere(Dado dado){
    insereNoFim(dado);
}

void lista::insereNoFim(Dado dado){
    noh *novo= new noh(dado);
    if(vazia()){
        primeiro=novo;
        ultimo=novo;
    }else{
        ultimo->proximo=novo;
        ultimo=novo;
    }
    tamanho++;    
}

void lista::insereNoInicio(Dado dado){
    noh *novo= new noh(dado);
    if(vazia()){
        primeiro=novo;
        ultimo=novo;
    }else{
        novo->proximo = primeiro;
        primeiro = novo;
    }
    tamanho++;
}

void lista::insereNaPosicao(int posicao, Dado dado){
    noh *novo= new noh(dado);
    if((posicao<=tamanho) and (posicao>=0)){
        if(vazia()){
            primeiro=novo;
            ultimo=novo;
        }else if(posicao==0){
            novo->proximo =primeiro;
            primeiro=novo;
        }else if(posicao==tamanho){
            ultimo->proximo=novo;
            ultimo = novo;
        }else{
            noh *aux =primeiro;
            int posAux =0;
            while(posAux <(posicao-1)){
                aux= aux->proximo;
                posAux++;
            }
            novo->proximo=aux->proximo;
            aux->proximo=novo;
        }
        tamanho++;
    }else{
        cerr<<"Posição Inexistente!"<<endl;
        exit(EXIT_FAILURE);
    }
}

int lista::procura(Dado valor){
    noh* aux = primeiro;
    int posAux =0;
    while((aux!=NULL) and (aux->dado!=valor)){
        posAux++;
        aux=aux->proximo;
    }
    if(aux==NULL){
        posAux=-1;
    }
    return posAux;
}

void lista::imprime(){
    noh *aux =primeiro;
    while(aux!=NULL){
        cout<< aux->dado<<" ";
        aux= aux->proximo;
    }
    cout<<endl;
}

void lista::imprimeReverso(noh *umNoh){
    if(umNoh!=NULL){
        imprimeReverso(umNoh->proximo);
        cout<<umNoh->dado<<" ";
    }
}

inline bool lista::vazia(){
    return(tamanho==0);
}

void lista::removeNoFim(){
    if(vazia()){
        cerr<< "Remoção em lista vazia!"<<endl;
        exit(EXIT_FAILURE);
    }
    noh *aux=primeiro;
    noh *anterior;
    while(aux->proximo!=NULL){
        anterior=aux;
        aux=aux->proximo;
    }
    delete ultimo;
    anterior->proximo=NULL;
    aux->proximo=NULL;
    ultimo=anterior;
    tamanho--;
    if(vazia())
        ultimo=NULL;
}

void lista::removeNoInicio(){
    if(vazia()){
        cerr<< "Remoção em lista vazia!"<<endl;
        exit(EXIT_FAILURE);
    }
    noh *removido = primeiro;
    primeiro = primeiro ->proximo;
    delete removido;
    tamanho--;
    if(vazia())
        ultimo=NULL;
}

