#include <iostream>
using namespace std;

struct midia{
	string nome;
	string responsavel;
	float valor;
};

struct entusiasta{
	string name;
	string obra;
	float valor;
	string email;
};

struct artista{
	string representante;
	string telefone;
	string endereco;
};

class curador{  //essa classe foi criada com o intuito de controlar todos as entidades em uma so 
	private:
		artista *famoso;
		midia *tv;
		entusiasta *fas;
	public:
		curador(int a, int b, int c);
		~curador();
		void biblioteca(int a, int b, int c);
		void cadastroFamoso(int a);
		void cadastroTv(int b);
		void cadastroFas(int c);
		void buscarArt(int a); //confere se o nome consta na lista
		void buscarEnt(int b);
		void buscarMid(int c);
		void escreverEnt(int posicao);
		void escreverMid(int posicao);
		void escreverArt(int posicao);
};

curador::curador(int a, int b, int c){ //inicializa os nossos ponteiros
	famoso=new artista[a];
	tv=new midia[b];
	fas=new entusiasta[c];
};

curador::~curador(){ //limpa tudo
	delete[] famoso;
	delete[] tv;
	delete[] fas;
};

void curador::cadastroFamoso(int a){
	system("clear||cls");
	cout<<"Bem vindo a sessao de cadastro dos artistas!!"<<endl<<endl;
	cout<<"VocÃª escolheu cadastrar "<<a<<" artista."<<endl;
	for(int i=0; i<a; i++){
		cout<<"Insira o nome do artista: "<<endl;
		cin.ignore();
		getline(cin, famoso[i].representante);
		cout<<"Insira o telefone: "<<endl;
		getline(cin, famoso[i].telefone);
		cout<<"Endereco: "<<endl;
		getline(cin, famoso[i].endereco);
		system("clear||cls");
	}
}

void curador::cadastroTv(int b){
	system("clear||cls");
	cout<<"Bem vindo a sessao de cadastro das formas midiaticas!!"<<endl<<endl;
	cout<<"VocÃª escolheu cadastrar "<<b<<" empresas."<<endl;
	for(int i=0; i<b; i++){
		cout<<"Insira o nome da empresa midiatica: "<<endl;
		cin.ignore();
		getline(cin, tv[i].nome);
		cout<<"Insira o responsavel: "<<endl;
		getline(cin, tv[i].responsavel);
		cout<<"E os valores dos ultimos contratos: "<<endl;
		cin>>tv[i].valor;
		system("clear||cls");
	}
}

void curador::cadastroFas(int c){
	system("clear||cls");
	cout<<"Bem vindo a sessao de cadastro dos entusiastas!!"<<endl<<endl;
	cout<<"VocÃª escolheu cadastrar "<<c<<" entusiastas."<<endl;
	for(int i=0; i<c; i++){
		cout<<"Insira o nome do entusiasta: "<<endl;
		cin.ignore();
		getline(cin, fas[i].name);
		cout<<"Insira o nome da ultima obra comprada por este: "<<endl;
		getline(cin, fas[i].obra);
		cout<<"Insira o valor dessa obra: "<<endl;
		cin>>fas[i].valor;
		cout<<"Insira o email de contato do entusiasta: "<<endl;
		cin>>fas[i].email;
		system("clear||cls");
	}
}

void curador::escreverArt(int posicao){ //escreve todos os dados de um determinado artista
	cout<<"Nome do artista: "<<endl;
	cout<<famoso[posicao].representante<<endl;
	cout<<"Numero de telefone: "<<endl;
	cout<<famoso[posicao].telefone<<endl;
	cout<<"Endereco: "<<endl;
	cout<<famoso[posicao].endereco<<endl;
}

void curador::buscarArt(int a){ //procura dados de um artista
	system("clear||cls");
	string desejo;
	bool v=false;
	cout<<"Qual nome deseja procurar? "<<endl;
	cin.ignore();
	getline(cin, desejo);
	for(int i=0; i<a; i++)
		if(desejo==famoso[i].representante){ //imprime as obras do artista
			v=true;
			escreverArt(i);
		}
	if(v==false) 
		cout<<"nÃ£o encontrado"<<endl;
}

void curador::escreverEnt(int posicao){ //escreve todos os dados de um determinado artista
	cout<<"Nome do entusiasta: "<<endl;
	cout<<fas[posicao].name<<endl;
	cout<<"Nome da ultima obra comprada: "<<endl;
	cout<<fas[posicao].obra<<endl;
	cout<<"Valor da ultima obra comprada: "<<endl;
	cout<<fas[posicao].valor<<endl;
	cout<<"Email do entusiasta: "<<endl;
	cout<<fas[posicao].email<<endl;
}

void curador::buscarEnt(int a){ //procura dados de um artista
	system("clear||cls");
	string desejo;
	bool v=false;
	cout<<"Qual nome do entusiasta deseja procurar? "<<endl;
	cin.ignore();
	getline(cin, desejo);
	for(int i=0; i<a; i++)
		if(desejo==fas[i].name){ //imprime as obras do artista
			v=true;
			escreverEnt(i);
		}
	if(v==false) 
		cout<<"nÃ£o encontrado"<<endl;
}

void curador::escreverMid(int posicao){ //escreve todos os dados de um determinado artista
	cout<<"Nome da empresa: "<<endl;
	cout<<tv[posicao].nome<<endl;
	cout<<"Nome do representante: "<<endl;
	cout<<tv[posicao].nome<<endl;
	cout<<"Valor cobrado: "<<endl;
	cout<<tv[posicao].valor<<endl;
}

void curador::buscarMid(int a){ //procura dados de um artista
	system("clear||cls");
	string desejo;
	bool v=false;
	cout<<"Qual empresa deseja procurar? "<<endl;
	cin.ignore();
	getline(cin, desejo);
	for(int i=0; i<a; i++)
		if(desejo==tv[i].nome){ //imprime as obras do artista
			v=true;
			escreverMid(i);
		}
	if(v==false) 
		cout<<"nÃ£o encontrado"<<endl;
}

void curador::biblioteca(int a, int b, int c){ // comanda qual busca deve fazer
	int var=-1;
	do{
		cout<<"O que vocÃª deseja procurar: "<<endl;
		cout<<"Caso vocÃª queira procurar por um artista digite 1"<<endl;
		cout<<"Caso queira uma forma de divulgaÃ§Ã£o midiatica digite 2"<<endl;
		cout<<"Caso queira um entusiasta pela arte digite 3"<<endl;
		cout<<"Caso nÃ£o queira terminar a pesquisa digite 0"<<endl;
		cin>>var;
		switch(var){
			case 1:
			buscarArt(a);
			break;
			case 2:
			buscarEnt(b);
			break;
			case 3:
			buscarMid(c);
			break;
		}
	}
	while(var!=0);
}


int main(){
	int quantFamoso, quantEntu, quantMidias;
	cout<<"Insira a quantidade de Artistas que deseja registrar:"<<endl;
	cin>>quantFamoso;
	cout<<"Insira a quantidade de Entusiastas que deseja registrar:"<<endl;
	cin>>quantEntu;
	cout<<"Insira a quantidade de Midias que deseja registrar:"<<endl;
	cin>>quantMidias;
	curador *contratador=new curador(quantFamoso, quantEntu, quantMidias);
	
	contratador->cadastroFamoso(quantFamoso);
	contratador->cadastroFas(quantEntu);
	contratador->cadastroTv(quantMidias);
	contratador->biblioteca(quantFamoso, quantEntu, quantMidias);
	system("clear||cls");
    return 0;
}
