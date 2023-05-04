#include <iostream>
using namespace std;

class pilha{
private:
    int topo;
    int tamanho;
    int dados[254];

public:
    pilha();
    void empilha(char valor);
    char desempilha();
    bool vazia();
    int tamanhos();
};

pilha::pilha(){
    tamanho = 0;
    topo=-1;
}

void pilha::empilha(char valor){
    if(tamanho<254){
        topo++;
        dados[topo] = valor;
        tamanho++;
    }else
        cout << "INVALIDO" << endl;
}
char pilha::desempilha(){
    char elemento = dados[topo];
    tamanho--;
    topo--;
    return elemento;
}

bool pilha::vazia(){
	return (tamanho==0);
}

int pilha::tamanhos(){
	return tamanho;
}

int main(){
    pilha p;
    string frase;
    getline(cin, frase);
    char a;
    int b=0;
    bool flag=true;
    for(unsigned int i=0; i<frase.size(); i++){
		a=frase[i];
		p.empilha(a);
        if(a==')'){
			b=p.tamanhos();
			while(a!='('){
				a=p.desempilha();
				if(p.vazia())
					flag=false;
			}
		}			
    }
    if(flag==true){
		while((not p.vazia()) and flag!=false){
			a=p.desempilha();
			if('('==a){
				b=p.tamanhos();
				flag=false;
			}
			if(p.tamanhos()==0)
				cout<<"correto"<<endl;
		}
	}else
		cout<<b<<endl;
    return 0;
}
