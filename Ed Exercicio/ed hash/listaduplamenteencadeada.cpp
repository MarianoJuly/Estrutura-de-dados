#include <iostream>
#include <cstdlib>
using namespace std;

typedef int Dado;

class noh{
    friend class listadupla;
private:
    const Dado dado;
    noh *proximo;
    noh *anterior;
public:
 noh(Dado d=0);
};

noh::noh(Dado d):dado(d){
    proximo= NULL;
    anterior=NULL;
};

class listadupla{
private:
    noh *primeiro;
    noh *ultimo;
    int tamanho;
    void removeTodos();
public:
    listadupla();
    ~listadupla();
    inline void insere(Dado dado);
    void insereNoFim(Dado dado);
    void imprime();
    inline bool vazia();
    void removeValor(Dado valor);
    void remove(listadupla& L2);
};

listadupla::listadupla(){
    primeiro=NULL;
    ultimo=NULL;
    tamanho=0;
}

listadupla::~listadupla(){
    removeTodos();
}

void listadupla::removeTodos(){
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


void listadupla::insere(Dado dado){
    insereNoFim(dado);
}

void listadupla::insereNoFim(Dado dado){
    noh *novo= new noh(dado);
    if(vazia()){
        primeiro=novo;
        ultimo=novo;
    }else{
        ultimo->proximo=novo;
        novo->anterior = ultimo;
        ultimo=novo;
    }
    tamanho++;    
}

void listadupla::imprime(){
    noh *aux =primeiro;
    while(aux!=NULL){
        cout<< aux->dado<<" ";
        aux= aux->proximo;
    }
    cout<<endl<<endl;
    //imprime reverso
    aux=ultimo;
    while(aux!=NULL){
        cout<<aux->dado<<" ";
        aux = aux->anterior;
    }
    cout<<endl;
}

inline bool listadupla::vazia(){
    return(tamanho==0);
}

void listadupla::removeValor(Dado valor){ //remove com base no valor
    noh *aux=primeiro;
    while(aux!=NULL){
        noh *aux3=aux;
        aux=aux->proximo;
        if(aux3->dado==valor){
            noh *anterior = aux3->anterior;
            noh *proximo = aux3->proximo;
            if(anterior!=NULL)
                anterior->proximo = proximo;
            else
                primeiro= aux3->proximo;
            if(proximo!=NULL)
                proximo->anterior= anterior;
            else
                ultimo = aux3 ->anterior;
            tamanho--;
            delete aux3;
        }
    }
    delete aux;
}

void listadupla::remove(listadupla &L2){
    noh *auxi=L2.primeiro;
    while(auxi!=NULL){
        removeValor(auxi->dado);
        auxi=auxi->proximo;
    }
}

int main(){
    listadupla L1;
    int valor, quantidade;
    cin>>quantidade;
    for(int i=0; i<quantidade; i++){
        cin>>valor;
        L1.insere(valor);
    }
    listadupla L2;
    cin>>quantidade;
    for(int i=0; i<quantidade; i++){
        cin>>valor;
        L2.insere(valor);
    }
    L1.remove(L2);
    if(!L1.vazia())
        L1.imprime();
    else
        cout<<"-1"<<endl;
    return 0;
}

