#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <stdlib.h>
using namespace std;

struct dadosAtleta{
	int id;
	char name[100];
	char team[100];
	char games[50];
	int year;
	char season[10];
};

int main(){
    ifstream arquivoBinario;
    arquivoBinario.open("binarioAtletas.bin", ios_base::out | ios_base::app | ios_base::binary);
    const long int tamanho_arquivo = arquivoBinario.tellg();
    const short tamanho_registro = sizeof(dadosAtleta);
    const long int qtd_registro = tamanho_arquivo/tamanho_registro;
    const int tamanho_pacotes = qtd_registro/2;
    cout<<tamanho_arquivo<<endl;
    cout<<tamanho_registro<<endl;
    cout<<qtd_registro<<endl;
    cout<<tamanho_pacotes<<endl;
    // Usando stringstream para pegar os dados em string
    // Primeiro getline pega uma linha, o segundo vai ser responsável pela separação dos dados
    dadosAtleta *atleta =new dadosAtleta[tamanho_arquivo];
    int contador=0;
    while(arquivoBinario.eof()){
        arquivoBinario.read((char*) (&atleta[contador]), sizeof(dadosAtleta[contador]));
        // Passando string para char em cada um dos dados do objeto atleta  
        cout << "ID: " << atleta[contador].id << " " 
             << "NOME: "<< atleta[contador].name << " " 
             << "TEAM: " << atleta[contador].team << " " 
             << "GAMES: "<< atleta[contador].games << " "  
             << "YEAR: "<< atleta[contador].year << " " 
             << "SEASON: "<< atleta[contador].season << endl;
            contador++;
        }
        arquivoBinario.close();
return 0;
}