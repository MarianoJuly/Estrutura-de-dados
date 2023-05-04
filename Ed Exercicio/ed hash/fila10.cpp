#include <iostream>
using namespace std;

class filaArranjo{
private:
    int mInicio;
    int mFim;
    int *mDados;
    unsigned mCapacidade;
    unsigned mPosicao;
public:
    filaArranjo(int mCapacidade);
    ~filaArranjo();
    void enfileira(int valor);
    int desenfileira();
    void subfila(int random);
};

filaArranjo::filaArranjo(int cap){
    mInicio=-1;
    mFim=-1;
    mCapacidade=cap;
    mDados=new int[mCapacidade];
    mPosicao=0;
}

filaArranjo::~filaArranjo(){
    delete[] mDados;
}

void filaArranjo::enfileira(int valor){
    if(mPosicao<=mCapacidade){
        mFim++;
        mDados[mFim]=valor;
        if(mPosicao==0)
            mInicio++;
        mCapacidade++;
    }else{
        cout<<"Pilha Cheia!"<<endl;
    }
}

int filaArranjo::desenfileira(){
    if(mPosicao>0){
        int valor=mDados[mInicio];
        mPosicao--;
        if(mPosicao>0){
            mInicio++;
        }else{
            mInicio=-1;
            mFim=-1;
        }
        return valor;
    }else{
        return -1;
    }
}

void filaArranjo::subfila(int random){
    bool flag=false;
    filaArranjo aux(random);
    int valor;
    while(!flag){
        for(int i=0; i<random; i++){
            valor=desenfileira();
            aux.enfileira(valor);
            if()
            
        }
        if(mCapacidade<3)
            flag=true;
    }

}

int main(){
    int cap;
    cin>>cap;
    filaArranjo fila(cap);
    int valor;
    for(int i=0; i<cap; i++){
        cin>>valor;
        fila.enfileira(valor);
    }
    cin>>cap;
    fila.subfila(cap);
    return 0;
}