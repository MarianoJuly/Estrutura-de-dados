#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <stdlib.h>
using namespace std;

//campos da base de dadosAtleta: id, name, team, games, year, season
//cria-se uma struct para receber os campos do arquivo
struct dadosAtleta{
	int id;
	char name[100];
	char team[100];
	char games[100];
	int year;
	char season[10];
};

int main(){
string linha; // variável do tipo string que recebe os campos do arquivo a ser lido 
char get; // variável auxiliar usada para tratar dos casos em que existe uma virgula dentro do campo que pode ser confundida com o separador do CSV
bool certeza= false; // bolleano para os casos de aspas
	
ifstream arquivo("data_athlete_game.csv", ios_base::in);//comando para abrir o arquivo
ofstream arquivoBinario;//comando que cria o arquivo binário
arquivoBinario.open("binarioAtletas.bin", ios_base::out | ios_base::app | ios_base::binary);//comando que abre o arquivo binário

	if(!arquivo){ //se o arquivo não foi corretamente aberto
		cerr << "Não foi possivél abrir o arquivo" << endl;
		exit(EXIT_FAILURE);
	}else{
		
		dadosAtleta atletas; // variável do tipo dadosAtleta que recebe os registros dos atletas
		while(!arquivo.eof()){//enquanto o arquivo não chegar ao fim

			getline(arquivo, linha, ',');// leitura do campo especifico sem necessidade de tratar aspas
			atletas.id = atoi(linha.c_str());
			linha.clear();

			arquivo >> get; //para a leitura do primeiro elemento do campo que pode ter aspas
			if(get == '"'){ // avalia se o char e uma aspas
				certeza= false;
				while(!certeza){  // enquanto não ter certeza que acabou o caso de aspas
					arquivo >> get;
					if('"'==get){ // se for aspas novamente vai avaliar se o proximo char vai ser virgula
						linha += get; // concatena numa string
						arquivo >> get;  // pega o proximo char
						if(get==',') // avalia se e virgula se sim certeza muda pra verdadeiro
							certeza = true;
					}else{ // para nao somar virgula desnecessaria
					linha += get; // soma os tipos char em uma string
					}
					//cout<<linha<<endl;
				}
				linha = "\"" + linha ;
				strcpy(atletas.name, linha.c_str());
				linha.clear();
			}else{ // caso não caia no caso aspas realizar  de forma simples
				getline(arquivo, linha, ',');
				linha = get + linha ;
				strcpy(atletas.name, linha.c_str());
				linha.clear();    
			}

			arquivo >> get; 
			if(get == '"'){
				certeza= false;
				while(!certeza){
					arquivo >> get;
					if('"'==get){
						linha += get;
						arquivo >> get;
						if(get==',')
							certeza = true;
					}else{
					linha += get;
					}
					//cout<<linha<<endl;
				}
				linha = "\"" + linha ;
				strcpy(atletas.team, linha.c_str());
				linha.clear();
			}else{
				getline(arquivo, linha, ',');
				linha = get + linha ;
				strcpy(atletas.team, linha.c_str());
				linha.clear();    
			}

			getline(arquivo, linha, ',');
			strcpy(atletas.games, linha.c_str());
			linha.clear();

			getline(arquivo, linha, ',');
			atletas.year = atoi(linha.c_str());
			linha.clear();

			getline(arquivo, linha, '\n');//leitura do campo season até o \n
			strcpy(atletas.season, linha.c_str());
			linha.clear();

			arquivoBinario.write((char*) (&atletas), sizeof(dadosAtleta));// escreve as informações da variável atletas no arquivo binário
			// cout << atletas.id << endl;
			}
		arquivo.close();
	}
return 0;
}
