#include <iostream>

typedef int Dado;

using namespace std;

class Noh{
    friend class ArvoreABB;
    private:
        Noh* mEsquerdo;
        Noh* mDireito;
        Noh* mPai;
        Dado valor;
        int contador;
    public:
        Noh(Dado d);
};

Noh::Noh(Dado d){
    //Construtor
    mEsquerdo = NULL;
    mDireito = NULL;
    mPai = NULL;
    valor = d;
    contador=0;
}

class ArvoreABB{
    private:
        Noh* mRaiz;
    public:
        ArvoreABB();
        ~ArvoreABB();
        void insere(Dado d);
        Noh* buscaAux(Noh* aux);
        void transplanta(Noh* antigo, Noh* novo);
        void remove(Dado d);
        Noh* minimoAux(Noh* atual);
        void imprimeOrdem(){ imprime(mRaiz);}
        void imprime(Noh* atual);
        void destrutor(Noh* atual);
        Dado Nivel(Dado chave);
};

ArvoreABB::ArvoreABB(){
    mRaiz = NULL;
}

ArvoreABB::~ArvoreABB(){
    destrutor(mRaiz);
}

void ArvoreABB::destrutor(Noh* atual){
    if(atual != NULL){
        destrutor(atual->mEsquerdo);
        destrutor(atual->mDireito);
        delete atual;
    }
}

void ArvoreABB::insere(Dado d){
    //Insere interativamente
    Noh* novo = new Noh(d);
    bool boleano= true;
    if(mRaiz == NULL){
        mRaiz = novo;
    } else {
        Noh* atual = mRaiz;
        Noh* ant = NULL;
        
        while(atual != NULL){
            ant = atual;
            if(novo->valor==atual->valor){
                boleano = false;
                atual->contador = atual->contador + 1;
                delete novo;
            }else if(atual -> valor > d){
                atual = atual -> mEsquerdo;
            } else {
                atual = atual -> mDireito;
            }
        }
        if(boleano==true){
            novo -> mPai = ant;
            if(ant -> valor > novo -> valor){
                ant -> mEsquerdo = novo;
            } else {
                ant -> mDireito = novo;
            }
        }
    }
}

Noh* ArvoreABB::buscaAux(Noh* aux){
    //Faz a busca na estrutura e retorna
    Noh* atual = mRaiz;
    while(atual != NULL){
        if(atual -> valor == aux -> valor){
            return atual;
        } else if(atual -> valor > aux -> valor){
            atual = atual -> mEsquerdo;
        } else {
            atual = atual -> mDireito;
        }
    }
    return atual;
}

void ArvoreABB::transplanta(Noh* antigo, Noh* novo){
    //Troca dois nos
    if(mRaiz == antigo){
        mRaiz = novo;
    } else if(antigo == antigo -> mPai -> mEsquerdo){
        antigo -> mPai -> mEsquerdo = novo;
    } else {
        antigo -> mPai -> mDireito = novo;
    }
    if(novo != NULL){
        novo -> mPai = antigo -> mPai;
    }
}

void ArvoreABB::remove(Dado d){
    //Remove um elemento (noh) da arvore
    Noh* aux = new Noh(d);
    Noh* remover = buscaAux(aux);
    if(remover == NULL){
        cout << "ERRO" << endl;
    } else {
        if(remover->contador==0){
            if(remover -> mEsquerdo == NULL){
                transplanta(remover, remover -> mDireito);
            } else if(remover -> mDireito == NULL){
				transplanta(remover, remover -> mEsquerdo);
            } else {
                Noh* sucessor = minimoAux(remover -> mDireito);
                if(sucessor -> mPai != remover){
                    transplanta(sucessor, sucessor -> mDireito);
                    sucessor -> mDireito = remover -> mDireito;
                    sucessor -> mDireito -> mPai = sucessor;
                }
                transplanta(remover, sucessor);
                sucessor -> mEsquerdo = remover -> mEsquerdo;
                sucessor -> mEsquerdo -> mPai = sucessor;
            }
            delete remover;
        }else{
            remover->contador = remover->contador - 1;
        }
    }
}

Noh* ArvoreABB::minimoAux(Noh* atual){
    //Retorna o minimo da arvore
    while(atual -> mEsquerdo != NULL){
        atual = atual -> mEsquerdo;
    }
    return atual;
}

void ArvoreABB::imprime(Noh* atual){
    if(atual != NULL){
        imprime(atual -> mEsquerdo);
        Dado altura = Nivel(atual->valor);
        cout << atual -> valor<<"("<< atual->contador <<")"<< "/" << altura << " ";
        imprime(atual -> mDireito);
    }
}

Dado ArvoreABB::Nivel(Dado chave){
    Noh* atual = mRaiz;
    Dado cont = 0;
    while(atual != NULL){
        if(atual->valor == chave){
            return cont;
        } else if(atual -> valor > chave){
            atual = atual -> mEsquerdo;
        } else {
            atual = atual -> mDireito;
        }
        cont++;
    }
    return cont;
}

int main(){
    ArvoreABB arvore;
    Dado valor;
    for (int i = 0; i < 10; ++i) {
        cin >> valor;
        arvore.insere(valor);
    }
    arvore.imprimeOrdem();
    for (int i = 0; i < 5; ++i) {
        cin >> valor;
        arvore.remove(valor);
    }
    arvore.imprimeOrdem();
    for (int i = 0; i < 10; ++i) {
        cin >> valor;
        arvore.insere(valor);
    }
    arvore.imprimeOrdem();
    for (int i = 0; i < 5; ++i) {
        cin >> valor;
        arvore.remove(valor);
    }
    arvore.imprimeOrdem();
	return 0;
}
