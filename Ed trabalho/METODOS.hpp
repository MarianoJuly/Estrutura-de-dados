#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <string>
#include <stdlib.h>
using namespace std;

#ifndef METODOS_HPP
#define METODOS_HPP

struct dadosAtleta{
	int id;
	char name[100];
	char team[100];
	char games[100];
	int year;
	char season[10];
};

void copiadadosAtletas (ifstream &arquivo, dadosAtleta atletas[], int posicaoBytes, int tamanhoPacotes){
    arquivo.seekg(posicaoBytes); // Posiciona a cabeça de leitura
    for (int i = 0; i < tamanhoPacotes; i++) //copiando as structs para vetor o de objetos
        arquivo.read((char*) &atletas[i], sizeof(atletas[i]));
}

void escrevedadosAtletas (ofstream &arquivo, dadosAtleta atletas[], int posicaoBytes, int tamanhoPacotes) {
    arquivo.seekp(posicaoBytes); // Posiciona a cabeça de leitura	
    for (int i = 0; i < tamanhoPacotes; i++) //escrevendo vetor de objetos no arquivo
        arquivo.write((char*) &atletas[i], sizeof(atletas[i]));
}

void imprime(dadosAtleta atleta){
    cout << atleta.id << ", ";
    cout << atleta.name << ", ";
    cout << atleta.games << ", ";
    cout << atleta.year << ", ";
    cout << atleta.season <<endl;
}

void intercalacaoInterna(dadosAtleta atletas[], int inicio, int meio, int fim, int escolha_ordenacao) {
    int i = inicio, j = meio;
    int tamanho = fim - inicio + 1;
    dadosAtleta *aux = new dadosAtleta[tamanho]; 
    int k = 0;

    while ((i < meio) and (j <= fim)) {
        if (escolha_ordenacao == 1) {                
            if (atletas[i].id <= atletas[j].id)  // mudei
                aux[k++] = atletas[i++]; 
            else  
                aux[k++] = atletas[j++]; 
        }
        else  {
            if (strcmp(atletas[i].name,atletas[j].name) < 0)  
                aux[k++] = atletas[i++];
            else  
                aux[k++] = atletas[j++];    
        } 
    }
	                           
    while (i < meio) {
        aux[k++] = atletas[i++];
    }
    
    while (j <= fim) {
        aux[k++] = atletas[j++]; 
    }
    
    for (int m = 0; m < tamanho; m++) 
        atletas[inicio + m] = aux[m];
}   

void  mergeSortInterno(dadosAtleta atletas[], int tam, int escolha_ordenacao) {
    int inicio, fim, bloco = 1;

    while (bloco < tam) {
        inicio = 0;

        while (inicio + bloco < tam) {
            fim = inicio + 2*bloco - 1;

            if (fim >= tam)  
                fim = tam - 1;

            intercalacaoInterna(atletas, inicio, inicio+bloco, fim, escolha_ordenacao);
            inicio = inicio + 2*bloco;
        }
        bloco = 2*bloco; // dobra o tamanho do bloco
    } 
}

void  intercalacaoExterna (ifstream auxE[2], ofstream &auxS, int passo, int escolha_ordenacao) { 
    dadosAtleta dados[2];
    // posição relativa de leitura em cada um dos arquivos 
    int pos[2] = {0,0};
    
    //variavél para informar se os dados do arquivo são válidos
    bool valido[2] = {false, false};

    while (((pos[0] + pos[1] )) < (2*passo)) {
        // incialmente verificamos se há dados para ser lidos
        if ((pos[0] < passo) and (! valido[0])) {
            /*tentamos ler o arquivo verificando se a leitura foi válida */
            if (auxE[0].read((char *) &dados[0] , sizeof(dadosAtleta))) 
                valido[0] = true;
            else 
                pos[0] = passo;
        }

        //repetimos o processo para o segundo arquivo
        if ((pos[1] < passo) and (! valido[1])) {
            if (auxE[1].read((char *) &dados[1] , sizeof(dadosAtleta))) 
                valido[1] = true;
            else 
                pos[1] = passo;
        }
            
        //1° caso, os dois dados são válidos 
        if (valido[0] and valido[1]) {
            if (dados[0].id <= dados[1].id and escolha_ordenacao == 1) {
                //gravamos o maior valor no arquivo de saída
                auxS.write((const char *) (&dados[0]), sizeof(dadosAtleta));
                valido[0] = false;
                pos[0]++;
            }
            else if ((strcmp(dados[0].name,dados[1].name) < 0) and escolha_ordenacao == 2) {
                //gravamos o menor valor no arquivo de saída 
                auxS.write((const char *) (&dados[0]), sizeof(dadosAtleta));
                valido[0] = false;
                pos[0]++;
            }
            else {
                auxS.write((const char *) (&dados[1].id), sizeof(dadosAtleta));
                valido[1] = false;
                pos[1]++;
            }          
        }
        //2° caso, apenas o primeiro dado é válido
        else if (valido[0]) {
            auxS.write((const char *) (&dados[0].id), sizeof(dadosAtleta)); 
            valido[0] = false;
            pos[0]++;
        }
        // 3° caso, apenas o segundo dado é válido
        else if (valido[1]) {
            auxS.write((const char *) (&dados[1].id), sizeof(dadosAtleta));
            valido[1] = false;
            pos[1]++;
        }
    }
}

void  mergeSortExterno (ofstream &arqSaida, int escolha_ordenacao, int qtd_dadosAtleta) {
    dadosAtleta umDado;

    //arquivos auxiliares
    ifstream auxEntrada[2];
    ofstream auxSaida;

    //variavel para controle no intercalamento
    int passo = (qtd_dadosAtleta/2) + 0.5;
   
    auxEntrada[0].open("arqTemp1.bin",ios::binary);
    auxEntrada[1].open("arqTemp2.bin",ios::binary);
    auxSaida.open("arqTemp3.bin",ios::binary);
   
    if ((! auxEntrada[0]) or (! auxEntrada[1]) or (! auxSaida)) {
        cerr << "Arquivos auxiliares não puderam ser abertos" << endl;
        exit(EXIT_FAILURE);
    }
    
    //enquanto não chegar ao final dos arquivos de entrada, vai intercalando o bloco
    while ((! auxEntrada[0].eof()) and (! auxEntrada[1].eof())) {
        intercalacaoExterna(auxEntrada,auxSaida,passo,escolha_ordenacao);
    }
        
    //fecha os arquivos para permitir troca (escrita<->leitura) na próxima interação
    auxEntrada[0].close();
    auxEntrada[1].close();
    auxSaida.close();   

    ifstream auxEnt;
    auxEnt.open ("arqTemp3.bin", ios::binary);
    
    if (! auxEnt) {
        cerr <<"Arquivo auxiliar não poder ser aberto" << endl;
        exit(EXIT_FAILURE);
    }

    //agora lemos do arquivo auxiliar para arquivo de saida
    while (auxEnt.read((char*)(&umDado),sizeof(dadosAtleta))) {
        arqSaida.write((const char*)(&umDado),sizeof(dadosAtleta));
    }

    auxEnt.close();
}

#endif 