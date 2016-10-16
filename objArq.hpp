#ifndef _OBJARQ_HPP_
#define _OBJARQ_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "objeto.hpp"

using namespace std;

class ObjArq{
public:
	ObjArq(FILE *);
	void inserir(vector<Objeto*> *);
private:
	vector<double> vertices;
	vector<int> ligacoes;
};

#endif
