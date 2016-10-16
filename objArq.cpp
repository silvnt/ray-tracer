#include "objArq.hpp"

ObjArq::ObjArq(FILE *arq){
	char tipo;
	
	while(1){
		fscanf(arq, "%c ", &tipo);
		if(tipo != 'v'){ break; }
		
		double vNovo1, vNovo2, vNovo3;
		
		fscanf(arq, " %lf  %lf  %lf\n", &vNovo1, &vNovo2, &vNovo3);
		
		vertices.push_back(vNovo1);
		vertices.push_back(vNovo2);
		vertices.push_back(vNovo3);
	}
	
	while(1){
		fscanf(arq, "%c ", &tipo);
		if(tipo != 'f'){ break; }
		
		int fNovo1, fNovo2, fNovo3;
		
		fscanf(arq, " %d  %d  %d\n", &fNovo1, &fNovo2, &fNovo3);
		
		ligacoes.push_back(fNovo1);
		ligacoes.push_back(fNovo2);
		ligacoes.push_back(fNovo3);
		
	}
	
}

void ObjArq::inserir(vector<Objeto*> *v){
	int i = -1, size = ligacoes.size();
	
	while(i < size-1){
		
		int posicV;
		
		i++;
		posicV = (ligacoes[i]-1) * 3;
		vec p1 = { vertices[posicV], vertices[posicV+1], vertices[posicV+2] };
		
		i++;
		posicV = (ligacoes[i]-1) * 3;
		vec p2 = { vertices[posicV], vertices[posicV+1], vertices[posicV+2] };
		
		i++;
		posicV = (ligacoes[i]-1) * 3;
		vec p3 = { vertices[posicV], vertices[posicV+1], vertices[posicV+2] };
		
		uvec color = { 126, 126, 126 };
		
		Objeto *novo = new Triangulo(p1, p2, p3, color);
		
		v->push_back(novo);
	}
}
