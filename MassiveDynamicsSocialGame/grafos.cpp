#include "grafos.h"
#include <iostream>
#include <fstream>

#define __GRAFO__FILE__ "normal.grafo"
using namespace std;
No nos[_MAX_NOS_GRAFO];
Arco arcos[_MAX_ARCOS_GRAFO];
int numNos = 0, numArcos = 0;
int noInicial;



void addNo(No no){
	if (numNos<_MAX_NOS_GRAFO){
		nos[numNos] = no;
		numNos++;
	}
	else{
		cout << "Número de nós chegou ao limite" << endl;
	}
}

void deleteNo(int indNo){
	if (indNo >= 0 && indNo<numNos){
		for (int i = indNo; i<numNos; nos[i++] = nos[i + i]);
		numNos--;
	}
	else{
		cout << "Indíce de nó inválido" << endl;
	}
}

void imprimeNo(No no){
	cout << "X:" << no.getX() << "Y:" << no.getY() << "Z:" << no.getZ() << endl;
}

void listNos(){
	for (int i = 0; i<numNos; imprimeNo(nos[i++]));
}



void addArco(Arco arco){
	if (numArcos<_MAX_ARCOS_GRAFO){
		arcos[numArcos] = arco;
		numArcos++;
	}
	else{
		cout << "Número de arcos chegou ao limite" << endl;
	}
}

void deleteArco(int indArco){
	if (indArco >= 0 && indArco<numArcos){
		for (int i = indArco; i<numArcos; arcos[i++] = arcos[i + i]);
		numArcos--;
	}
	else{
		cout << "Indíce de arco inválido" << endl;
	}
}

void imprimeArco(Arco arco){
	cout << "No início:" << arco.getNOI() << "Nó final:" << arco.getNOF() << "Peso:" << arco.getPeso() << "Largura:" << arco.getLargura() << endl;
}

void listArcos(){
	for (int i = 0; i<numArcos; imprimeArco(arcos[i++]));
}


void gravaGrafo(){
	ofstream myfile;

	myfile.open(__GRAFO__FILE__, ios::out);
	if (!myfile.is_open()) {
		cout << "Erro ao abrir " << __GRAFO__FILE__ << "para escrever" << endl;
		exit(1);
	}
	myfile << numNos << endl;
	for (int i = 0; i<numNos; i++)
		myfile << nos[i].getX() << " " << nos[i].getY() << " " << nos[i].getZ() << endl;
	myfile << numArcos << endl;
	for (int i = 0; i<numArcos; i++)
		myfile << arcos[i].getNOI() << " " << arcos[i].getNOF() << " " << arcos[i].getPeso() << " " << arcos[i].getLargura() << endl;
	myfile.close();
}
void leGrafo(){
	ifstream myfile;

	myfile.open(__GRAFO__FILE__, ios::in);
	if (!myfile.is_open()) {
		cout << "Erro ao abrir " << __GRAFO__FILE__ << "para ler" << endl;
		exit(1);
	}
	myfile >> numNos;
	for (int i = 0; i < numNos; i++){
		myfile >> nos[i].x >> nos[i].y >> nos[i].z;
		nos[i].tipo = 'N';
	}
	int no_tipo;
	myfile >> no_tipo;
	nos[no_tipo].tipo = 'I';
	noInicial = no_tipo;
	myfile >> no_tipo;
	nos[no_tipo].tipo = 'F';
	myfile >> no_tipo;
	nos[no_tipo].tipo = 'B';
	myfile >> numArcos;
	for (int i = 0; i<numArcos; i++)
		myfile >> arcos[i].noi >> arcos[i].nof >> arcos[i].peso >> arcos[i].largura;
	myfile.close();
	// calcula a largura de cada no = maior largura dos arcos que divergem/convergem desse/nesse no	
	for (int i = 0; i<numNos; i++){
		nos[i].largura = 0.0;
		for (int j = 0; j<numArcos; j++)
		if ((arcos[j].getNOI() == i || arcos[j].getNOF() == i) && nos[i].getLargura() < arcos[j].getLargura())
			nos[i].largura = arcos[j].getLargura();
	}
}