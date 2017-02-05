#ifndef _OBJARQ_HPP_
#define _OBJARQ_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "objeto.hpp"
#include <string>

using namespace std;

class ObjArq{
public:
	ObjArq(char *);
	void inserir(vector<Objeto*> *);
private:
	//Parametros de arquivo .obj
	vector<double> vertices;
	vector<double> normais;
	vector<int> ligacoesVert; //posic. vertices - arestas
	vector<int> ligacoesNorm; //normais correspondentes aos vertices
	vector<int> positObjVert; //posic. vertices - onde termina det. cor
	
	//Parametros de arquivo .mtl
	char mtlArqName[128]; //nome do arquivo .mtl
	void readMtl(); //funcao de leitura do .mtl
	vector<double> shinenessIntensidades;
	vector<uvec> difusaCores;
	vector<uvec> especularCores;
};

#endif
