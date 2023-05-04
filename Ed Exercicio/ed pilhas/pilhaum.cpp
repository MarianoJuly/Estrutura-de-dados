#include <iostream>
using namespace std;

class noh{
    friend class pilha;
    private:
        int mValor;
        noh *mNext;
    public:
        noh(int valor);
};

noh::noh(int valor){
    mValor=valor;
    mNext=NULL;
}

class pilha{
private:
    noh* mTopo;
    unsigned mTamanho;
public:
    pilha();
    ~pilha();
    unsigned tamanho();
    void empilha(int dado);
    void limpaPilha();
    int desempilha();
    bool vazia();
};

pilha::pilha(){
    mTopo= NULL;
    mTamanho=0;
}

pilha::~pilha(){
    limpaPilha();
}

void pilha::limpaPilha(){
    while(mTamanho>0)
        desempilha();
}

unsigned pilha::tamanho(){
    return mTamanho;
}

void pilha::empilha(int valor){
    noh* novo= new noh(valor);
    novo->mNext=mTopo;
    mTopo=novo;
    mTamanho++;
}

    int pilha::desempilha(){
        int valor= mTopo->mValor;
        noh* tempo= mTopo;
        mTopo=mTopo->mNext;
        delete tempo;
        mTamanho--;
        return valor;
    }

bool pilha::vazia(){
    return (mTamanho==0);
}


int main(){
    pilha p1;
    int num;
    cin>>num;
    while (num>=0){
        p1.empilha(num);
        cin>>num;
    }

    cout<<p1.tamanho()<<endl;
    while (not p1.vazia()){
        printf("%d \n", p1.desempilha());
    }
    return 0;
}