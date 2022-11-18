#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include "METODOS.hpp"
using namespace std;

int main () {
    ifstream arquivoBinario;
    arquivoBinario.open("binarioAtletas.bin", ios::in | ios::binary);

    if (!arquivoBinario) {
        cerr << "Não foi possivél abrir o arquivo" << endl;
        exit(EXIT_FAILURE);
    }

    arquivoBinario.seekg(0,ios::end);

    const long int tamanhoArquivo = arquivoBinario.tellg();
    const short tamanhoRegistro = sizeof(dadosAtleta);
    const long int qtdDados = tamanhoArquivo / tamanhoRegistro;
    const int tamanhoPacotes = qtdDados/2;

    dadosAtleta *atletas = new dadosAtleta[tamanhoPacotes];

    short escolha;
    int posicaoBytes;

    if (arquivoBinario) { 
        cout << "Digite, ordenar por:\n" 
             << "\n(1) ID"
             << "\n(2)  Nome\n\n->";

        cin >> escolha;

        if ((escolha != 1 ) and (escolha != 2)) {
            cerr << "\"Opção inexistente\"" << endl;
            exit(EXIT_FAILURE);
        }
    }
    else {
        cerr << "Não foi possivél ler o arquivo" << endl;
        exit(EXIT_FAILURE);
    }
	
    ofstream arqTemp1("arqTemp1.bin", ios::binary);
    ofstream arqTemp2("arqTemp2.bin", ios::binary);
	
    if((! arqTemp1) or (! arqTemp2)) {
        cerr << "Não foi possivél abrir o arquivo" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        for (int cont = 0; cont < 2; cont++) {	
            posicaoBytes = tamanhoRegistro * (cont * tamanhoPacotes);

            copiadadosAtletas(arquivoBinario, atletas, posicaoBytes, tamanhoPacotes);

            mergeSortInterno(atletas,tamanhoPacotes,escolha);	
		
            if (cont == 0) 
                escrevedadosAtletas(arqTemp1, atletas, 0, tamanhoPacotes);
            else 
                escrevedadosAtletas(arqTemp2, atletas, 0, tamanhoPacotes);
        }
    	delete [] atletas;
    }

    arquivoBinario.close();
    arqTemp1.close();
    arqTemp2.close();
	
    ofstream arquivoFinal("arquivoFinalOrdenado.bin",ios::binary);
	
    mergeSortExterno(arquivoFinal,escolha,qtdDados);

	cout << "\n\n\'Ordenação Feita com Sucesso\'\n" << endl;
	
    arquivoFinal.close();

	//apagar arquivos auxiliares
    remove("arqTemp1.bin");
    remove("arqTemp2.bin");
    remove("arqTemp3.bin");

    cout << "\nGostaria de testar a ordenação ?\n" 
		 << "\nDigite (1) Sim ou (2) Não\n-> ";
	
	cin >> escolha;

	if (escolha == 1) {
        cout<<"\n Deseja imprimir todos os dados ou uma quantidade especifica?"
            <<"\n Caso queira todos digite (1), caso queira imprimir todos digite (2):\n->";

        cin>>escolha;

        if(escolha==1){
            cout << "\nQuantos de dados você deseja imprimir?\n-> ";

            int quantidade;

            cin >> quantidade;

            if (quantidade <= qtdDados and quantidade > 0) {
                dadosAtleta *aux= new dadosAtleta[qtdDados];
                ifstream arq("arquivoFinalOrdenado.bin",ios::binary);
                
                copiadadosAtletas(arq, aux, 0, qtdDados);

                for(int i = 0; i < quantidade; i++) 
                    imprime(aux[i]);

                arq.close();
                delete [] aux;

            } else {
                cerr << "\nQuantidade inválida!" << endl;
                exit(EXIT_FAILURE);
            }

        }else{
            dadosAtleta *aux= new dadosAtleta[qtdDados];
            ifstream arq("arquivoFinalOrdenado.bin",ios::binary);
            
            arq.seekg(0);

            for(int i=0; !arq.eof(); i++){
                arq.read((char*) &aux[i], sizeof(aux[i]));
                imprime(aux[i]);
            }
        }
	}
	
    return 0;
}