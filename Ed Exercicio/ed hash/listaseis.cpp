#include <iostream>

using namespace std;

typedef int Dado;

class noh {
    friend class lista;
    private:
        const Dado dado;
        noh* proximo;
    public:
        noh(Dado d = 0);
};

noh::noh(Dado d) : dado(d) {
    proximo = NULL;
}

class lista {
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
    public:
        lista();
        ~lista();
        void insere(Dado dado);
        void insere(Dado dado, int pos);
        void remove(int posicao);
        void removeFim();
        void removeIni();
        int procura(Dado valor);
        void imprime();
        inline bool vazia();
};

// constrói uma lista inicialmente vazia
lista::lista() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

// destrutor de lista
lista::~lista() {
    noh* iter = primeiro;
    noh* proximo = NULL;
    while (iter != NULL) {
        proximo = iter->proximo;
        delete iter;
        iter = proximo;
    }
}

// método básico que *percorre* a lista, imprimindo seus elementos
void lista::imprime() {
    noh* aux = primeiro;
    while (aux != NULL) {
        cout << aux->dado << " ";
        aux = aux->proximo;
    }
    cout << endl;
}

// insere por padrão no final da lista
void lista::insere(Dado dado) {
    noh *novo = new noh(dado);
    if(vazia()) {
        primeiro = novo;
        ultimo = novo;
    }else {
        ultimo -> proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

// insere um dado em uma determinada posição da lista
void lista::insere(Dado dado, int posicao) {
    noh *novo = new noh(dado);
    if((posicao <= tamanho) and (posicao >= 0)) {
        if(vazia()) {
            primeiro = novo;
            ultimo = novo;
        }else if(posicao == 0) {
            novo -> proximo = primeiro;
            primeiro = novo;
        }else if(posicao == tamanho) {
            ultimo -> proximo = novo;
            ultimo = novo;
        }else {
            noh *aux = primeiro;
            int posiAux = 0;
            while(posiAux < (posicao - 1)) {
                aux = aux -> proximo;
                posiAux++;
            }
            novo -> proximo = aux -> proximo;
            aux -> proximo = novo;
        }
         tamanho++;
    }else {
        cerr << "Esta posição não existe" << endl;
        exit(EXIT_FAILURE);
    }
}
// remove o item da posição passada por parâmetro
void lista::remove(int posicao) {
    noh *aux = primeiro;
    noh *anterior;
    int posiAux = 0;
    while((aux != NULL) and (posiAux < posicao)) {
      anterior = aux;
      aux = aux -> proximo;
      posiAux++;
    }
    if(aux != NULL) {
        if(aux == primeiro) {
            removeIni();
        }else if(aux == ultimo) {
            removeFim();
        }else {
            anterior -> proximo = aux -> proximo;
            tamanho--;
            delete aux;
        }
    }else {
        cerr << "Esta posição não existe" << endl;
        exit(EXIT_FAILURE);
    }
}

// procura por um elemento e retorna a posição ou -1 se não encontrado
int lista::procura(Dado valor) {
    noh *aux = primeiro;
    int posiAux = 0;
    while((aux != NULL) and (aux -> dado != valor)) {
        posiAux++;
        aux = aux -> proximo;
    }
    if(aux == NULL) {
        posiAux = -1;
    }
    return posiAux;
}

// verifica se a lista está vazia
inline bool lista::vazia() {
    return(primeiro == NULL);
}

// faz a remoção pelo fim
void lista::removeFim() {
    if(vazia()) {
        cerr << "Remoção em lista vazia!" << endl;
        exit(EXIT_FAILURE);
    }
    noh *aux = primeiro;
    noh *anterior;
    while(aux -> proximo != NULL) {
        anterior = aux;
        aux = aux -> proximo;
    }
    delete ultimo;
    anterior -> proximo = NULL;
    aux -> proximo = NULL;
    ultimo = aux;
    tamanho--;
    if(vazia()) {
        primeiro = NULL;
    }
}

// remove pelo inicio
void lista::removeIni() {
    if(vazia()) {
        cerr << "Remoção em lista vazia!" << endl;
        exit(EXIT_FAILURE);
    }
    noh *removido = primeiro;
    primeiro = primeiro -> proximo;
    delete removido;
    tamanho--;
    if(vazia()) {
        ultimo = NULL;
    }
}

int main() { 
    lista minhaLista;
    char opcao;
    int valor, pos;
    cin >> opcao;
    while (opcao != 'Q') {
        switch(opcao) {
            case 'I':
                cin >> valor;
                minhaLista.insere(valor);
                break;
            case 'W':
                cin >> valor;
                cin >> pos;
                minhaLista.insere(valor, pos);
                break;
            case 'P':
                cin >> valor;
                cout << minhaLista.procura(valor) << endl;
                break;
            case 'R':
                cin >> pos;
                minhaLista.remove(pos);
                break;
            case 'V':
                cout << minhaLista.vazia() << endl;
                break;
        }
        cin >> opcao;
    }
    minhaLista.imprime();
    return 0;
}